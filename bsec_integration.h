/**
 * @file bsec_integration.h
 * @brief Contains BSEC integration API
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef __BSEC_INTEGRATION_H__
#define __BSEC_INTEGRATION_H__

#ifdef __cplusplus
extern "C"
{
#endif

/**********************************************************************************************************************/
/* header files */
/**********************************************************************************************************************/

/* Use the following bme680 driver: https://github.com/BoschSensortec/BME680_driver/releases/tag/bme680_v3.5.1 */
#include "bme680.h"
/* BSEC header files are available in the inc/ folder of the release package */
#include "bsec_interface.h"
#include "bsec_datatypes.h"


/**********************************************************************************************************************/
/* type definitions */
/**********************************************************************************************************************/

/* function pointer to the system specific sleep function */
typedef void (*sleep_fct)(uint32_t t_ms);

/* function pointer to the system specific timestamp derivation function */
typedef int64_t (*get_timestamp_us_fct)();

/* function pointer to the function processing obtained BSEC outputs */
typedef void (*output_ready_fct)(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature, float humidity,
    float pressure, float raw_temperature, float raw_humidity, float gas, bsec_library_return_t bsec_status);

/* function pointer to the function loading a previous BSEC state from NVM */
typedef uint32_t (*state_load_fct)(uint8_t *state_buffer, uint32_t n_buffer);

/* function pointer to the function saving BSEC state to NVM */
typedef void (*state_save_fct)(const uint8_t *state_buffer, uint32_t length);

/* function pointer to the function loading the BSEC configuration string from NVM */
typedef uint32_t (*config_load_fct)(uint8_t *state_buffer, uint32_t n_buffer);
    
typedef struct{
  int8_t bme680_status;              /**< Result of API execution status */
  bsec_library_return_t bsec_status; /**< Result of BSEC library */
}return_values_init;

/**
 * @fn bsec_iot_init
 * @brief Initialize the BME680 sensor and the BSEC library
 *
 * @param sample_rate         mode to be used (either BSEC_SAMPLE_RATE_ULP or BSEC_SAMPLE_RATE_LP)
 * @param temperature_offset  device-specific temperature offset (due to self-heating)
 * @param bus_write           pointer to the bus writing function
 * @param bus_read            pointer to the bus reading function
 * @param sleep               pointer to the system-specific sleep function
 * @param state_load          pointer to the system-specific state load function
 *
 * @return      zero if successful, negative otherwise
 */
return_values_init bsec_iot_init(float sample_rate, float temperature_offset, bme680_com_fptr_t bus_write, bme680_com_fptr_t bus_read, 
    sleep_fct sleep, uint8_t addr, enum bme680_intf intf);

/**
 * @fn bsec_iot_loop
 * @brief       Runs the main (endless) loop that queries sensor settings, applies them, and processes the measured data
 *
 * @param sleep               pointer to the system-specific sleep function
 * @param get_timestamp_us    pointer to the system-specific timestamp derivation function
 * @param output_ready        pointer to the function processing obtained BSEC outputs
 * @param state_save          pointer to the system-specific state save function
 * @param save_intvl          interval at which BSEC state should be saved (in samples)
 *
 * @return      return_values_init	struct with the result of the API and the BSEC library
 */ 
int8_t bsec_iot_loop(sleep_fct sleep, get_timestamp_us_fct get_timestamp_us, output_ready_fct output_ready);

#ifdef __cplusplus
}
#endif

#endif /* __BSEC_INTEGRATION_H__ */

/*! @}*/

