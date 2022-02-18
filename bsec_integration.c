/**
 * @file bsec_integration.c
 * @brief Private part of the example for using of BSEC library.
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "bsec_integration.h"

#include "Arduino.h"

/**********************************************************************************************************************/
/* local macro definitions */
/**********************************************************************************************************************/

#define NUM_USED_OUTPUTS 7

/**********************************************************************************************************************/
/* global variable declarations */
/**********************************************************************************************************************/

/* Global sensor APIs data structure */
static struct bme680_dev bme680_g;

/* Global temperature offset to be subtracted */
static float bme680_temperature_offset_g = 0.0f;

/**********************************************************************************************************************/
/* functions */
/**********************************************************************************************************************/

/**
 * @fn bme680_bsec_update_subscription
 * @brief Virtual sensor subscription.Please call this function before processing of data using bsec_do_steps function.
 * @param sample_rate  mode to be used (either BSEC_SAMPLE_RATE_ULP or BSEC_SAMPLE_RATE_LP)
 * @return subscription result, zero when successful
 */
static bsec_library_return_t bme680_bsec_update_subscription(float sample_rate)
{
    bsec_sensor_configuration_t requested_virtual_sensors[NUM_USED_OUTPUTS];
    uint8_t n_requested_virtual_sensors = NUM_USED_OUTPUTS;
    
    bsec_sensor_configuration_t required_sensor_settings[BSEC_MAX_PHYSICAL_SENSOR];
    uint8_t n_required_sensor_settings = BSEC_MAX_PHYSICAL_SENSOR;
    
    bsec_library_return_t status = BSEC_OK;
    
    /* note: Virtual sensors as desired to be added here */
    requested_virtual_sensors[0].sensor_id = BSEC_OUTPUT_IAQ_ESTIMATE;
    requested_virtual_sensors[0].sample_rate = sample_rate;
    requested_virtual_sensors[1].sensor_id = BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE;
    requested_virtual_sensors[1].sample_rate = sample_rate;
    requested_virtual_sensors[2].sensor_id = BSEC_OUTPUT_RAW_PRESSURE;
    requested_virtual_sensors[2].sample_rate = sample_rate;
    requested_virtual_sensors[3].sensor_id = BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY;
    requested_virtual_sensors[3].sample_rate = sample_rate;
    requested_virtual_sensors[4].sensor_id = BSEC_OUTPUT_RAW_GAS;
    requested_virtual_sensors[4].sample_rate = sample_rate;
    requested_virtual_sensors[5].sensor_id = BSEC_OUTPUT_RAW_TEMPERATURE;
    requested_virtual_sensors[5].sample_rate = sample_rate;
    requested_virtual_sensors[6].sensor_id = BSEC_OUTPUT_RAW_HUMIDITY;
    requested_virtual_sensors[6].sample_rate = sample_rate;
    
    /* Call bsec_update_subscription() to enable/disable the requested virtual sensors */
    status = bsec_update_subscription(requested_virtual_sensors, n_requested_virtual_sensors, required_sensor_settings,
        &n_required_sensor_settings);
    
    return status;
}

/**
 * @fn bsec_iot_init
 * @brief  Initialize the BME680 sensor and the BSEC library
 *
 * @param   sample_rate         mode to be used (either BSEC_SAMPLE_RATE_ULP or BSEC_SAMPLE_RATE_LP)
 * @param   temperature_offset  device-specific temperature offset (due to self-heating)
 * @param   bus_write           pointer to the bus writing function
 * @param   bus_read            pointer to the bus reading function
 * @param   sleep               pointer to the system specific sleep function
 * @param   state_load          pointer to the system-specific state load function
 * @param   config_load         pointer to the system-specific config load function
 *
 * @return      zero if successful, negative otherwise
 */
return_values_init bsec_iot_init(float sample_rate, float temperature_offset, bme680_com_fptr_t bus_write, 
                    bme680_com_fptr_t bus_read, sleep_fct sleep, uint8_t addr, enum bme680_intf intf)
{
    return_values_init ret = {BME680_OK, BSEC_OK};
    bsec_library_return_t bsec_status = BSEC_OK;
    
    uint8_t bsec_state[BSEC_MAX_PROPERTY_BLOB_SIZE] = {0};
    uint8_t bsec_config[BSEC_MAX_PROPERTY_BLOB_SIZE] = {0};
    uint8_t work_buffer[BSEC_MAX_PROPERTY_BLOB_SIZE] = {0};
    int bsec_state_len, bsec_config_len;
    
    /* Fixed I2C configuration */
    bme680_g.dev_id = addr;
    bme680_g.intf = intf;
    /* User configurable I2C configuration */
    bme680_g.write = bus_write;
    bme680_g.read = bus_read;
    bme680_g.delay_ms = sleep;
    
    /* Initialize BME680 API */
    ret.bme680_status = bme680_init(&bme680_g);
	if (ret.bme680_status != BME680_OK)
	{
		return ret;
	}
    
    /* Initialize BSEC library */
    ret.bsec_status = bsec_init();
    if (ret.bsec_status != BSEC_OK)
    {
        return ret;
    }
    
    /* Set temperature offset */
    bme680_temperature_offset_g = temperature_offset;
    
    /* Call to the function which sets the library with subscription information */
    ret.bsec_status = bme680_bsec_update_subscription(sample_rate);
    if (ret.bsec_status != BSEC_OK)
    {
        return ret;
    }
    
    return ret;
}

/**
 * @fn bme680_bsec_trigger_measurement
 * @brief Trigger the measurement based on sensor settings
 *
 * @param sensor_settings     settings of the BME680 sensor adopted by sensor control function
 * @param sleep               pointer to the system specific sleep function
 *
 * @return   uint32_t
 */
static uint32_t bme680_bsec_trigger_measurement(bsec_bme_settings_t *sensor_settings, sleep_fct sleep)
{
	uint16_t meas_period;
	uint8_t set_required_settings;
    int8_t bme680_status = BME680_OK;
        
    /* Check if a forced-mode measurement should be triggered now */
    if (sensor_settings->trigger_measurement)
    {
        /* Set sensor configuration */

        bme680_g.tph_sett.os_hum  = sensor_settings->humidity_oversampling;
        bme680_g.tph_sett.os_pres = sensor_settings->pressure_oversampling;
        bme680_g.tph_sett.os_temp = sensor_settings->temperature_oversampling;
		bme680_g.gas_sett.run_gas = sensor_settings->run_gas;
		bme680_g.gas_sett.heatr_temp = sensor_settings->heater_temperature; /* degree Celsius */
		bme680_g.gas_sett.heatr_dur  = sensor_settings->heating_duration; /* milliseconds */
		
		/* Select the power mode */
		/* Must be set before writing the sensor configuration */
		bme680_g.power_mode = BME680_FORCED_MODE;
		/* Set the required sensor settings needed */
		set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_GAS_SENSOR_SEL;
		
		/* Set the desired sensor configuration */
        bme680_status = bme680_set_sensor_settings(set_required_settings, &bme680_g);
             
        /* Set power mode as forced mode and trigger forced mode measurement */
        bme680_status = bme680_set_sensor_mode(&bme680_g);
        
		/* Get the total measurement duration so as to sleep or wait till the measurement is complete */
		bme680_get_profile_dur(&meas_period, &bme680_g);
        
        /* Delay till the measurement is ready. Timestamp resolution in ms */
        return ((uint32_t)meas_period);
    } else return 0;
}

/**
 * @fn bme680_bsec_read_data
 * @brief       Read the data from registers and populate the inputs structure to be passed to do_steps function
 *
 * @param[in]   time_stamp_trigger      settings of the sensor returned from sensor control function
 * @param[in]   inputs                  input structure containing the information on sensors to be passed to do_steps
 * @param[in]   num_bsec_inputs         number of inputs to be passed to do_steps
 * @param[in]   bsec_process_data       process data variable returned from sensor_control
 *
 * @return      none
 */
static void bme680_bsec_read_data(int64_t time_stamp_trigger, bsec_input_t *inputs, uint8_t *num_bsec_inputs, int32_t bsec_process_data)
{
    static struct bme680_field_data data;
    int8_t bme680_status = BME680_OK;
    
    /* We only have to read data if the previous call the bsec_sensor_control() actually asked for it */
    if (bsec_process_data)
    {
        bme680_status = bme680_get_sensor_data(&data, &bme680_g);

        if (data.status & BME680_NEW_DATA_MSK)
        {
            /* Pressure to be processed by BSEC */
            if (bsec_process_data & BSEC_PROCESS_PRESSURE)
            {
                /* Place presssure sample into input struct */
                inputs[*num_bsec_inputs].sensor_id = BSEC_INPUT_PRESSURE;
                inputs[*num_bsec_inputs].signal = data.pressure;
                inputs[*num_bsec_inputs].time_stamp = time_stamp_trigger;
                (*num_bsec_inputs)++;
            }
            /* Temperature to be processed by BSEC */
            if (bsec_process_data & BSEC_PROCESS_TEMPERATURE)
            {
                /* Place temperature sample into input struct */
                inputs[*num_bsec_inputs].sensor_id = BSEC_INPUT_TEMPERATURE;
                inputs[*num_bsec_inputs].signal = data.temperature / 100.0f;
                inputs[*num_bsec_inputs].time_stamp = time_stamp_trigger;
                (*num_bsec_inputs)++;
                
                /* Also add optional heatsource input which will be subtracted from the temperature reading to 
                 * compensate for device-specific self-heating (supported in BSEC IAQ solution)*/
                inputs[*num_bsec_inputs].sensor_id = BSEC_INPUT_HEATSOURCE;
                inputs[*num_bsec_inputs].signal = bme680_temperature_offset_g;
                inputs[*num_bsec_inputs].time_stamp = time_stamp_trigger;
                (*num_bsec_inputs)++;
            }
            /* Humidity to be processed by BSEC */
            if (bsec_process_data & BSEC_PROCESS_HUMIDITY)
            {
                /* Place humidity sample into input struct */
                inputs[*num_bsec_inputs].sensor_id = BSEC_INPUT_HUMIDITY;
                inputs[*num_bsec_inputs].signal = data.humidity / 1000.0f;
                inputs[*num_bsec_inputs].time_stamp = time_stamp_trigger;
                (*num_bsec_inputs)++;
            }
            /* Gas to be processed by BSEC */
            if (bsec_process_data & BSEC_PROCESS_GAS)
            {
                /* Check whether gas_valid flag is set */
                if(data.status & BME680_GASM_VALID_MSK)
                {
                    /* Place sample into input struct */
                    inputs[*num_bsec_inputs].sensor_id = BSEC_INPUT_GASRESISTOR;
                    inputs[*num_bsec_inputs].signal = data.gas_resistance;
                    inputs[*num_bsec_inputs].time_stamp = time_stamp_trigger;
                    (*num_bsec_inputs)++;
                }
            }
        }
    }
}

/**
 * @fn bme680_bsec_process_data
 * @brief       This function is written to process the sensor data for the requested virtual sensors
 *
 * @param[in]   bsec_inputs         input structure containing the information on sensors to be passed to do_steps
 * @param[in]   num_bsec_inputs     number of inputs to be passed to do_steps
 * @param[in]   output_ready        pointer to the function processing obtained BSEC outputs
 *
 * @return      none
 */
static void bme680_bsec_process_data(bsec_input_t *bsec_inputs, uint8_t num_bsec_inputs, output_ready_fct output_ready)
{
    /* Output buffer set to the maximum virtual sensor outputs supported */
    bsec_output_t bsec_outputs[BSEC_NUMBER_OUTPUTS];
    uint8_t num_bsec_outputs = 0;
    uint8_t index = 0;

    bsec_library_return_t bsec_status = BSEC_OK;
    
    int64_t timestamp = 0;
    float iaq = 0.0f;
    uint8_t iaq_accuracy = 0;
    float temp = 0.0f;
    float raw_temp = 0.0f;
    float raw_pressure = 0.0f;
    float humidity = 0.0f;
    float raw_humidity = 0.0f;
    float raw_gas = 0.0f;
    
    /* Check if something should be processed by BSEC */
    if (num_bsec_inputs > 0)
    {
        /* Set number of outputs to the size of the allocated buffer */
        /* BSEC_NUMBER_OUTPUTS to be defined */
        num_bsec_outputs = BSEC_NUMBER_OUTPUTS;
        
        /* Perform processing of the data by BSEC 
           Note:
           * The number of outputs you get depends on what you asked for during bsec_update_subscription(). This is
             handled under bme680_bsec_update_subscription() function in this example file.
           * The number of actual outputs that are returned is written to num_bsec_outputs. */
        bsec_status = bsec_do_steps(bsec_inputs, num_bsec_inputs, bsec_outputs, &num_bsec_outputs);
        
        /* Iterate through the outputs and extract the relevant ones. */
        for (index = 0; index < num_bsec_outputs; index++)
        {
            switch (bsec_outputs[index].sensor_id)
            {
                case BSEC_OUTPUT_IAQ_ESTIMATE:
                    iaq = bsec_outputs[index].signal;
                    iaq_accuracy = bsec_outputs[index].accuracy;
                    break;
                case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE:
                    temp = bsec_outputs[index].signal;
                    break;
                case BSEC_OUTPUT_RAW_PRESSURE:
                    raw_pressure = bsec_outputs[index].signal;
                    break;
                case BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY:
                    humidity = bsec_outputs[index].signal;
                    break;
                case BSEC_OUTPUT_RAW_GAS:
                    raw_gas = bsec_outputs[index].signal;
                    break;
                case BSEC_OUTPUT_RAW_TEMPERATURE:
                    raw_temp = bsec_outputs[index].signal;
                    break;
                case BSEC_OUTPUT_RAW_HUMIDITY:
                    raw_humidity = bsec_outputs[index].signal;
                    break;
                default:
                    continue;
            }
            
            /* Assume that all the returned timestamps are the same */
            timestamp = bsec_outputs[index].time_stamp;
        }
        
        /* Pass the extracted outputs to the user provided output_ready() function. */
        output_ready(timestamp, iaq, iaq_accuracy, temp, humidity, raw_pressure, raw_temp, 
            raw_humidity, raw_gas, bsec_status);
    }
}
int8_t bsec_iot_loop(sleep_fct sleep, get_timestamp_us_fct get_timestamp_us, output_ready_fct output_ready)
{
    /* Timestamp variables */
    static int64_t time_stamp = 0;
    static int64_t time_stamp_interval_ms = 0;
    
    /* Allocate enough memory for up to BSEC_MAX_PHYSICAL_SENSOR physical inputs*/
    static bsec_input_t bsec_inputs[BSEC_MAX_PHYSICAL_SENSOR];
    
    /* Number of inputs to BSEC */
    static uint8_t num_bsec_inputs = 0;
    
    /* BSEC sensor settings struct */
    static bsec_bme_settings_t sensor_settings;
    
    /* Save state variables */
    static uint8_t bsec_state[BSEC_MAX_PROPERTY_BLOB_SIZE];
    static uint8_t work_buffer[BSEC_MAX_PROPERTY_BLOB_SIZE];
    static uint32_t bsec_state_len = 0;
    static uint32_t n_samples = 0;
    
    static bsec_library_return_t bsec_status = BSEC_OK;

    static uint32_t waitTime = 0;
    static unsigned long lastTime = 0;

    if(waitTime == 0) {
      /* get the timestamp in nanoseconds before calling bsec_sensor_control() */
      time_stamp = get_timestamp_us() * 1000;
      
      /* Retrieve sensor settings to be used in this time instant by calling bsec_sensor_control */
      bsec_sensor_control(time_stamp, &sensor_settings);
      
      /* Trigger a measurement if necessary */
      lastTime = millis();
      waitTime = bme680_bsec_trigger_measurement(&sensor_settings, sleep);
      return 1;
    } else if((millis() - lastTime) >= waitTime) {
      waitTime = 0;
      /* Call the API to get current operation mode of the sensor */
      bme680_get_sensor_mode(&bme680_g);

      /* When the measurement is completed and data is ready for reading, the sensor must be in BME680_SLEEP_MODE.
       * Read operation mode to check whether measurement is completely done and wait until the sensor is no more
       * in BME680_FORCED_MODE. */
      while (bme680_g.power_mode == BME680_FORCED_MODE)
      {
          /* sleep for 5 ms */
          sleep(5);
          bme680_get_sensor_mode(&bme680_g);
      }
      
      /* Read data from last measurement */
      num_bsec_inputs = 0;
      bme680_bsec_read_data(time_stamp, bsec_inputs, &num_bsec_inputs, sensor_settings.process_data);
      
      /* Time to invoke BSEC to perform the actual processing */
      bme680_bsec_process_data(bsec_inputs, num_bsec_inputs, output_ready);
      return 0;
    }
    return 1;
}

/*! @}*/

