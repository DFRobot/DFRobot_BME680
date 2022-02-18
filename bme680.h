/*!
 * @file bme680.h
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef BME680_H_
#define BME680_H_

/*! CPP guard */
#ifdef __cplusplus
extern "C"
{
#endif

/* Header includes */
#include "bme680_defs.h"

/**
 * @fn bme680_init
 * @brief This API is the entry point.
 * @n It reads the chip-id and calibration data from the sensor.
 * @param dev : Structure instance of bme680_dev
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_init(struct bme680_dev *dev);

/**
 * @fn bme680_set_regs
 * @brief This API writes the given data to the register address of the sensor.
 * @param reg_addr : Register address from where the data to be written.
 * @param reg_data : Pointer to data buffer which is to be written in the sensor.
 * @param len : No of bytes of data to write..
 * @param dev : Structure instance of bme680_dev.
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_set_regs(const uint8_t *reg_addr, const uint8_t *reg_data, uint8_t len, struct bme680_dev *dev);

/**
 * @fn bme680_get_regs
 * @brief This API reads the data from the given register address of the sensor.
 * @param reg_addr : Register address from where the data to be read
 * @param reg_data : Pointer to data buffer to store the read data.
 * @param len : No of bytes of data to be read.
 * @param dev : Structure instance of bme680_dev.
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_get_regs(uint8_t reg_addr, uint8_t *reg_data, uint16_t len, struct bme680_dev *dev);

/**
 * @fn bme680_soft_reset
 * @brief This API performs the soft reset of the sensor.
 * @param dev : Structure instance of bme680_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
int8_t bme680_soft_reset(struct bme680_dev *dev);

/**
 * @fn bme680_set_sensor_mode
 * @brief This API is used to set the power mode of the sensor.
 * @param dev : Structure instance of bme680_dev
 * @note : Pass the value to bme680_dev.power_mode structure variable.
 * @n value	|	mode
 * @n ------|------------------
 * @n 0x00	|	BME680_SLEEP_MODE
 * @n 0x01	|	BME680_FORCED_MODE
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_set_sensor_mode(struct bme680_dev *dev);

/**
 * @brief This API is used to get the power mode of the sensor.
 * @param dev : Structure instance of bme680_dev
 * @note : bme680_dev.power_mode structure variable hold the power mode.
 * @n
 * @n  value	|	mode
 * @n  ---------|------------------
 * @n	0x00	|	BME680_SLEEP_MODE
 * @n	0x01	|	BME680_FORCED_MODE
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_get_sensor_mode(struct bme680_dev *dev);

/**
 * @brief This API is used to set the profile duration of the sensor.
 * @param dev	   : Structure instance of bme680_dev.
 * @param duration : Duration of the measurement in ms.
 * @return Nothing
 */
void bme680_set_profile_dur(uint16_t duration, struct bme680_dev *dev);

/**
 * @fn bme680_get_profile_dur
 * @brief This API is used to get the profile duration of the sensor.
 *
 * @param duration : Duration of the measurement in ms.
 * @param dev	   : Structure instance of bme680_dev.
 * @return Nothing
 */
void bme680_get_profile_dur(uint16_t *duration, const struct bme680_dev *dev);

/**
 * @fn bme680_get_sensor_data
 * @brief This API reads the pressure, temperature and humidity and gas data
 * @n from the sensor, compensates the data and store it in the bme680_data
 * @n structure instance passed by the user.
 * @param data: Structure instance to hold the data.
 * @param dev : Structure instance of bme680_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error
 */
int8_t bme680_get_sensor_data(struct bme680_field_data *data, struct bme680_dev *dev);

/**
 * @fn bme680_set_sensor_settings
 * @brief This API is used to set the oversampling, filter and T,P,H, gas selection settings in the sensor.
 *
 * @param desired_settings : Variable used to select the settings which are to be set in the sensor.
 * @n 
 * @n 	 Macros	                   |  Functionality
 * @n ---------------------------------|----------------------------------------------
 * @n 	BME680_OST_SEL             |    To set temperature oversampling.
 * @n 	BME680_OSP_SEL             |    To set pressure oversampling.
 * @n 	BME680_OSH_SEL             |    To set humidity oversampling.
 * @n 	BME680_GAS_MEAS_SEL        |    To set gas measurement setting.
 * @n 	BME680_FILTER_SEL          |    To set filter setting.
 * @n 	BME680_HCNTRL_SEL          |    To set humidity control setting.
 * @n 	BME680_RUN_GAS_SEL         |    To set run gas setting.
 * @n 	BME680_NBCONV_SEL          |    To set NB conversion setting.
 * @n 	BME680_GAS_SENSOR_SEL      |    To set all gas sensor related settings
 * @param dev : Structure instance of bme680_dev.
 *
 * @note : Below are the macros to be used by the user for selecting the
 * @n desired settings. User can do OR operation of these macros for configuring multiple settings.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
int8_t bme680_set_sensor_settings(uint16_t desired_settings, struct bme680_dev *dev);

/**
 * @fn bme680_get_sensor_settings
 * @brief This API is used to get the oversampling, filter and T,P,H, gas selection
 * @n settings in the sensor.
 *
 * @param desired_settings : Variable used to select the settings which
 * @n are to be get from the sensor.
 * @param dev : Structure instance of bme680_dev.
 *
 * @return Result of API execution status
 * @retval zero -> Success / +ve value -> Warning / -ve value -> Error.
 */
int8_t bme680_get_sensor_settings(uint16_t desired_settings, struct bme680_dev *dev);

uint32_t calc_gas_resistance(uint16_t gas_res_adc, uint8_t gas_range, struct bme680_dev *dev);
#ifdef __cplusplus
}
#endif 
#endif