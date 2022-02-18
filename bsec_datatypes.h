/*!
 * @file bme680_defs.h
 * @brief Contains the data types used by BSEC
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef __BSEC_DATATYPES_H__
#define __BSEC_DATATYPES_H__

#ifdef __cplusplus
extern "C"
{
#endif


#ifdef __KERNEL__
#include <linux/types.h>
#endif
#include <stdint.h>
#include <stddef.h>

#define BSEC_MAX_PHYSICAL_SENSOR     (6)              ///< Number of physical sensors that need allocated space before calling bsec_update_subscription() */
#define BSEC_MAX_PROPERTY_BLOB_SIZE  (400)            ///< Maximum size (in bytes) of the data blobs returned by bsec_get_state() and bsec_get_configuration() */
#define BSEC_SAMPLE_RATE_DISABLED    (65535.0f)       ///< Sample rate of a disabled sensor */
#define BSEC_SAMPLE_RATE_ULP         (0.0033333f)     ///< Sample rate in case of Ultra Low Power Mode */
#define BSEC_SAMPLE_RATE_LP          (0.33333f)       ///< Sample rate in case of Low Power Mode */

#define BSEC_PROCESS_PRESSURE       (1 << (BSEC_INPUT_PRESSURE-1))      ///< process_data bitfield constant for pressure @sa bsec_bme_settings_t */
#define BSEC_PROCESS_TEMPERATURE    (1 << (BSEC_INPUT_TEMPERATURE-1))   ///< process_data bitfield constant for temperature @sa bsec_bme_settings_t */
#define BSEC_PROCESS_HUMIDITY       (1 << (BSEC_INPUT_HUMIDITY-1))      ///< process_data bitfield constant for humidity @sa bsec_bme_settings_t */
#define BSEC_PROCESS_GAS            (1 << (BSEC_INPUT_GASRESISTOR-1))   ///< process_data bitfield constant for gas sensor @sa bsec_bme_settings_t */
#define BSEC_NUMBER_OUTPUTS         (13)                                ///< Number of outputs, depending on solution */
#define BSEC_OUTPUT_INCLUDED        (4250095)                           ///< bitfield that indicates which outputs are included in the solution */

/**
 * @enum bsec_physical_sensor_t
 * @brief Enumeration for input (physical) sensors.
 * @n Used to populate bsec_input_t::sensor_id. It is also used in bsec_sensor_configuration_t::sensor_id structs
 * @n returned in the parameter required_sensor_settings of bsec_update_subscription()
 * @sa bsec_sensor_configuration_t 
 * @sa bsec_input_t
 */
typedef enum
{
    BSEC_INPUT_PRESSURE = 1,    /**< Pressure sensor output of BMExxx [Pa]*/
    BSEC_INPUT_HUMIDITY = 2,    /**< Humidity sensor output of BMExxx [%] 
    Relative humidity strongly depends on the temperature (it is measured at). It may required a convertion to
    the temperature outside of the device.  */
    BSEC_INPUT_TEMPERATURE = 3, /**< Temperature sensor output of BMExxx [degrees Celcius]
    The BME680 is factory trimmed, thus the temperature sensor of the BME680 is very accurate. 
    The temperature value is a very local measurement value and can be influenced by external heat sources. */    
    BSEC_INPUT_GASRESISTOR = 4, /**< Gas sensor resistance output of BMExxx [Ohm]
    The restistance value changes due to varying VOC concentrations (the higher the concentration of reducing VOCs, 
    the lower the resistance and vice versa).  */
    BSEC_INPUT_HEATSOURCE = 14, /**< Additional input for device heat compensation
    IAQ solution: The value is substracted from ::BSEC_INPUT_TEMPERATURE to compute 
    ::BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE.
    ALL solution: Generic heatsource 1*/

} bsec_physical_sensor_t;

/**
 * @enum bsec_virtual_sensor_t
 * @brief Enumeration for output (virtual) sensors.
 * @n Used to populate bsec_output_t::sensor_id. It is also used in bsec_sensor_configuration_t::sensor_id structs 
 * @n passed in the parameter requested_virtual_sensors of bsec_update_subscription().
 * @sa bsec_sensor_configuration_t @sa bsec_output_t
 */
typedef enum
{
    BSEC_OUTPUT_IAQ_ESTIMATE = 1,  /** Indoor-air-qualiy estimate [0-500]. Indoor-air-quality (IAQ) gives an indication of 
    the relative change in ambient TVOCs detected by BME680. 
    The IAQ scale ranges from 0 (clean air) to 500 (heavily polluted air). During operation, algorithms 
    automatically calibrate and adapt themselves to the typical environments where the sensor is operated 
    (e.g., home, workplace, inside a car, etc.).This automatic background calibration ensures that users experience 
    consistent IAQ performance. The calibration process considers the recent measurement history (typ. up to four 
    days) to ensure that IAQ=25 corresponds to typical good air and IAQ=250 indicates typical polluted air.*/                         
    BSEC_OUTPUT_RAW_TEMPERATURE = 6,  /**< Temperature sensor signal [degrees Celcius]. Temperature directly measured by BME680 in degree Celcius. 
    This value is cross-influenced by the sensor heating and device specific heating.*/              
    BSEC_OUTPUT_RAW_PRESSURE = 7,  /**< Pressure sensor signal [Pa]. Pressure directly measured by the BME680 in Pa.*/            
    BSEC_OUTPUT_RAW_HUMIDITY = 8,  /**< Relative humidity sensor signal [%] .Relative humidity directly measured by the BME680 in %.
    This value is cross-influenced by the sensor heating and device specific heating. */
    BSEC_OUTPUT_RAW_GAS = 9, /**< Gas sensor signal [Ohm]. 
    Gas resistance measured directly by the BME680 in Ohm.The restistance value changes due to varying VOC 
    concentrations (the higher the concentration of reducing VOCs, the lower the resistance and vice versa).*/               
    BSEC_OUTPUT_STABILIZATION_STATUS = 12, /**< Gas sensor stabilization status [boolean]
    Indicates initial stabilization status of the gas sensor element: stabilization is ongoing (0) or stablization is finished (1).*/                
    BSEC_OUTPUT_RUN_IN_STATUS = 13,   /**< Gas sensor run-in status [boolean].
    Indicates power-on stabilization status of the gas sensor element: stabilization is ongoing (0) or stablization is finished (1).*/                      
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE = 15,  /**< Sensor heat compensated temperature [degrees Celcius]
    Temperature measured by BME680 which is compensated for the influence of sensor (heater) in degree Celcius. 
    The self heating introduced by the heater is depending on the sensor operation mode and the sensor supply voltage.*/
    BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY = 16,   /**<  Sensor heat compensated humidity [%]. Relative measured by BME680 which is compensated for the influence of sensor (heater) in %.
    It converts the ::BSEC_INPUT_HUMIDITY from temperature ::BSEC_INPUT_TEMPERATURE to temperature::BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE.
    IAQ soultion: If ::BSEC_INPUT_HEATSOURCE is used for device specific temperature compensation, it will be
    effective for ::BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY too.*/ 

} bsec_virtual_sensor_t;

/**
 * 
 * @brief Enumeration for function return codes 
 */
typedef enum
{
    BSEC_OK = 0,                                    /**< Function execution successful */
    BSEC_E_DOSTEPS_INVALIDINPUT = -1,               /**< Input (physical) sensor id passed to bsec_do_steps() is not in the valid range or not valid for requested virtual sensor */
    BSEC_E_DOSTEPS_VALUELIMITS = -2,                /**< Value of input (physical) sensor signal passed to bsec_do_steps() is not in the valid range */
    BSEC_E_DOSTEPS_DUPLICATEINPUT = -6,             /**< Duplicate input (physical) sensor ids passed as input to bsec_do_steps() */
    BSEC_I_DOSTEPS_NOOUTPUTSRETURNABLE = 2,         /**< No memory allocated to hold return values from bsec_do_steps(), i.e., n_outputs == 0 */
    BSEC_W_DOSTEPS_EXCESSOUTPUTS = 3,               /**< Not enough memory allocated to hold return values from bsec_do_steps(), i.e., n_outputs < maximum number of requested output (virtual) sensors */
    BSEC_W_DOSTEPS_TSINTRADIFFOUTOFRANGE = 4,       /**< Duplicate timestamps passed to bsec_do_steps() */
    BSEC_E_SU_WRONGDATARATE = -10,                  /**< The sample_rate of the requested output (virtual) sensor passed to bsec_update_subscription() is zero */
    BSEC_E_SU_SAMPLERATELIMITS = -12,               /**< The sample_rate of the requested output (virtual) sensor passed to bsec_update_subscription() does not match with the sampling rate allowed for that sensor */
    BSEC_E_SU_DUPLICATEGATE = -13,                  /**< Duplicate output (virtual) sensor ids requested through bsec_update_subscription() */
    BSEC_E_SU_INVALIDSAMPLERATE = -14,              /**< The sample_rate of the requested output (virtual) sensor passed to bsec_update_subscription() does not fall within the global minimum and maximum sampling rates  */
    BSEC_E_SU_GATECOUNTEXCEEDSARRAY = -15,          /**< Not enough memory allocated to hold returned input (physical) sensor data from bsec_update_subscription(), i.e., n_required_sensor_settings < #BSEC_MAX_PHYSICAL_SENSOR */
    BSEC_E_SU_SAMPLINTVLINTEGERMULT = -16,          /**< The sample_rate of the requested output (virtual) sensor passed to bsec_update_subscription() is not correct */
    BSEC_E_SU_MULTGASSAMPLINTVL = -17,              /**< The sample_rate of the requested output (virtual), which requires the gas sensor, is not equal to the sample_rate that the gas sensor is being operated */
    BSEC_E_SU_HIGHHEATERONDURATION = -18,           /**< The duration of one measurement is longer than the requested sampling interval */
    BSEC_W_SU_UNKNOWNOUTPUTGATE = 10,               /**< Output (virtual) sensor id passed to bsec_update_subscription() is not in the valid range; e.g., n_requested_virtual_sensors > actual number of output (virtual) sensors requested */
    BSEC_I_SU_SUBSCRIBEDOUTPUTGATES = 12,           /**< No output (virtual) sensor data were requested via bsec_update_subscription() */
    BSEC_E_PARSE_SECTIONEXCEEDSWORKBUFFER = -32,    /**< n_work_buffer_size passed to bsec_set_[configuration/state]() not sufficient */
    BSEC_E_CONFIG_FAIL = -33,                       /**< Configuration failed */
    BSEC_E_CONFIG_VERSIONMISMATCH = -34,            /**< Version encoded in serialized_[settings/state] passed to bsec_set_[configuration/state]() does not match with current version */
    BSEC_E_CONFIG_FEATUREMISMATCH = -35,            /**< Enabled features encoded in serialized_[settings/state] passed to bsec_set_[configuration/state]() does not match with current library implementation */
    BSEC_E_CONFIG_CRCMISMATCH = -36,                /**< serialized_[settings/state] passed to bsec_set_[configuration/state]() is corrupted */
    BSEC_E_CONFIG_EMPTY = -37,                      /**< n_serialized_[settings/state] passed to bsec_set_[configuration/state]() is to short to be valid */
    BSEC_E_CONFIG_INSUFFICIENTWORKBUFFER = -38,     /**< Provided work_buffer is not large enough to hold the desired string */
    BSEC_E_CONFIG_INVALIDSTRINGSIZE = -40,          /**< String size encoded in configuration/state strings passed to bsec_set_[configuration/state]() does not match with the actual string size n_serialized_[settings/state] passed to these functions */
    BSEC_E_CONFIG_INSUFFICIENTBUFFER = -41,         /**< String buffer nsufficient to hold serialized data from BSEC library */
    BSEC_E_SET_INVALIDCHANNELIDENTIFIER = -100,     /**< Internal error code */
    BSEC_E_SET_INVALIDLENGTH = -104,                /**< Internal error code */
    BSEC_W_SC_CALL_TIMING_VIOLATION = 100,          /**< Difference between actual and defined sampling intervals of bsec_sensor_control() greater than allowed */
} bsec_library_return_t;

/**
 * @struct bsec_version_t
 * @brief Structure containing the version information
 * @n Please note that configuration and state strings are coded to a specific version and will not be accepted by other 
 * @n versions of BSEC.
 * 
 */
typedef struct
{
    uint8_t major;        /**< Major version */
    uint8_t minor;        /**< Minor version */
    uint8_t major_bugfix; /**< Major bug fix version */
    uint8_t minor_bugfix; /**< Minor bug fix version */
} bsec_version_t;

/**
 * @struct bsec_input_t
 * @brief Time stamp in nanosecond resolution [ns]. Structure describing an input sample to the library
 * @n Each input sample is provided to BSEC as an element in a struct array of this type. Timestamps must be provided 
 * @n in nanosecond  resolution. Moreover, duplicate timestamps for subsequent samples are not allowed and will results in 
 * @n an error code being returned from bsec_do_steps().
 *
 * @n The meaning unit of the signal field are determined by the bsec_input_t::sensor_id field content. Possible 
 * @n bsec_input_t::sensor_id values and and their meaning are described in ::bsec_physical_sensor_t.
 *
 * @sa bsec_physical_sensor_t
 * 
 */
typedef struct
{
    int64_t time_stamp;         /**< Time stamp in nanosecond resolution [ns].
    Timestamps must be provided as non-repeating and increasing values. They can have their 0-points at system start or
    at a defined wall-clock time (e.g., 01-Jan-1970 00:00:00)*/    
    float signal;               /**< @brief Signal sample in the unit defined for the respective sensor_id @sa bsec_physical_sensor_t */
    uint8_t signal_dimensions;  /**< @brief Signal dimensions (reserved for future use, shall be set to 1) */
    uint8_t sensor_id;          /**< @brief Identifier of physical sensor @sa bsec_physical_sensor_t */
} bsec_input_t;

/**
 * @struct bsec_output_t
 * @brief Structure describing an output sample of the library.
 * @n Each output sample is returned from BSEC by populating the element of a struct array of this type. The contents of 
 * @n the signal field is defined by the supplied bsec_output_t::sensor_id. Possible output bsec_output_t::sensor_id values 
 * @n are defined in ::bsec_virtual_sensor_t. 
 * @sa bsec_virtual_sensor_t
 */
typedef struct
{
    int64_t time_stamp;         /**< @brief Time stamp in nanosecond resolution as provided as input [ns] */
    float signal;               /**< @brief Signal sample in the unit defined for the respective bsec_output_t::sensor_id @sa bsec_virtual_sensor_t */
    uint8_t signal_dimensions;  /**< @brief Signal dimensions (reserved for future use, shall be set to 1) */
    uint8_t sensor_id;          /**< @brief Identifier of virtual sensor @sa bsec_virtual_sensor_t  */  
    uint8_t accuracy;    /**< Accuracy status 0-4 
    Some virtual sensors provide a value in the accuracy field. If this is the case, the meaning of the field is as follows:
    | Name                       | Value |  Accuracy description                                       |
    |----------------------------|-------|-------------------------------------------------------------|
    | UNRELIABLE                 |   0   | Sensor data is unreliable, the sensor must be calibrated    |
    | LOW_ACCURACY               |   1   | Low accuracy, sensor should be calibrated                   |
    | MEDIUM_ACCURACY            |   2   | Medium accuracy, sensor calibration may improve performance |
    | HIGH_ACCURACY              |   3   | High accuracy                                               |
    For example:
    - Ambient temperature accuracy is derived from change in the temperature in 1 minute.
    
      | Virtual sensor       | Value |  Accuracy description                                                        |
      |--------------------- |-------|------------------------------------------------------------------------------|
      | Ambient temperature  |   0   | The difference in ambient temperature is greater than 4 degree in one minute |
      |                      |   1   | The difference in ambient temperature is less than 4 degree in one minute    |
      |                      |   2   | The difference in ambient temperature is less than 3 degree in one minute    |
      |                      |   3   | The difference in ambient temperature is less than 2 degree in one minute    |
    
    - IAQ accuracy indicator will notify the user when she/he should initiate a calibration process. Calibration is 
      performed automatically in the background if the sensor is exposed to clean and polluted air for approximately 
      30 minutes each.
    
      | Virtual sensor             | Value |  Accuracy description                                           |
      |----------------------------|-------|-----------------------------------------------------------------|
      | IAQ                        |   0   | The sensor is not yet stablized or in a run-in status           |
      |                            |   1   | Calibration required                                            |
      |                            |   2   | Calibration on-going                                            |
      |                            |   3   | Calibration is done, now IAQ estimate achieves best perfomance  |*/      
} bsec_output_t;

/**
 * @struct bsec_sensor_configuration_t
 * @brief Structure describing sample rate of physical/virtual sensors
 * @n This structure is used together with bsec_update_subscription() to enable BSEC outputs and to retrieve information
 * @n about the sample rates used for BSEC inputs.
 */
typedef struct
{
    float sample_rate; /**< Sample rate of the virtual or physical sensor in Hertz [Hz]. Only supported sample rates are allowed.*/          
    uint8_t sensor_id;              /**< Identifier of the virtual or physical sensor.
    The meaning of this field changes depening on whether the structs are as the requested_virtual_sensors argument
    to bsec_update_subscription() or as the required_sensor_settings argument.
    | bsec_update_subscription() argument | sensor_id field interpretation |
    |-------------------------------------|--------------------------------|
    | requested_virtual_sensors           | ::bsec_virtual_sensor_t        |
    | required_sensor_settings            | ::bsec_physical_sensor_t       |*/
} bsec_sensor_configuration_t;

/**
 * @struct bsec_bme_settings_t
 * @brief Structure returned by bsec_sensor_control() to configure BMExxx sensor  
 *
 * @n This structure contains settings that must be used to configure the BMExxx to perform a forced-mode measurement. 
 * @n A measurement should only be executed if bsec_bme_settings_t::trigger_measurement is 1. If so, the oversampling 
 * @n settings for temperature, humidity, and pressure should be set to the provided settings provided in 
 * @n bsec_bme_settings_t::temperature_oversampling, bsec_bme_settings_t::humidity_oversampling, and
 * @n bsec_bme_settings_t::pressure_oversampling, respectively. 
 *
 * @n In case of bsec_bme_settings_t::run_gas = 1, the gas sensor must be enabled with the provided 
 * @n bsec_bme_settings_t::heater_temperature and bsec_bme_settings_t::heating_duration settings.
 */
typedef struct
{
    int64_t next_call;                  /**< Time stamp of the next call of the sensor_control*/
    uint32_t process_data;              /**< Bit field describing which data is to be passed to bsec_do_steps() @sa BSEC_PROCESS_* */
    uint16_t heater_temperature;        /**< Heating temperature [degrees Celsius] */
    uint16_t heating_duration;          /**< Heating duration [ms] */
    uint8_t run_gas;                    /**< Enable gas measurements [0/1] */
    uint8_t pressure_oversampling;      /**< Pressure oversampling settings [0-5] */
    uint8_t temperature_oversampling;   /**< Temperature oversampling settings [0-5] */
    uint8_t humidity_oversampling;      /**< Humidity oversampling settings [0-5] */
    uint8_t trigger_measurement;        /**< Trigger a forced measurement with these settings now [0/1] */
} bsec_bme_settings_t;

/* internal defines and backward compatbility */
#define BSEC_STRUCT_NAME            Bsec                       ///< Internal struct name


#ifdef __cplusplus
}
#endif

#endif
