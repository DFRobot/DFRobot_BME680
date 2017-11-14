/**
*
****************************************************************************
* Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
*
* File : bme680_calculations.h
*
* Date: 5 May 2017
*
* Revision : 2.2.0 $
*
* Usage: Sensor Driver for BME680 sensor
*
****************************************************************************
*
* \section Disclaimer
*
* Common:
* Bosch Sensortec products are developed for the consumer goods industry.
* They may only be used within the parameters of the respective valid
* product data sheet.  Bosch Sensortec products are provided with the
* express understanding that there is no warranty of fitness for a
* particular purpose.They are not fit for use in life-sustaining,
* safety or security sensitive systems or any system or device
* that may lead to bodily harm or property damage if the system
* or device malfunctions. In addition,Bosch Sensortec products are
* not fit for use in products which interact with motor vehicle systems.
* The resale and or use of products are at the purchasers own risk and
* his own responsibility. The examination of fitness for the intended use
* is the sole responsibility of the Purchaser.
*
* The purchaser shall indemnify Bosch Sensortec from all third party
* claims, including any claims for incidental, or consequential damages,
* arising from any product use not covered by the parameters of
* the respective valid product data sheet or not approved by
* Bosch Sensortec and reimburse Bosch Sensortec for all costs in
* connection with such claims.
*
* The purchaser must monitor the market for the purchased products,
* particularly with regard to product safety and inform Bosch Sensortec
* without delay of all security relevant incidents.
*
* Engineering Samples are marked with an asterisk (*) or (e).
* Samples may vary from the valid technical specifications of the product
* series. They are therefore not intended or fit for resale to third
* parties or for use in end products. Their sole purpose is internal
* client testing. The testing of an engineering sample may in no way
* replace the testing of a product series. Bosch Sensortec assumes
* no liability for the use of engineering samples.
* By accepting the engineering samples, the Purchaser agrees to indemnify
* Bosch Sensortec from all claims arising from the use of engineering
* samples.
*
* Special:
* This software module (hereinafter called "Software") and any information
* on application-sheets (hereinafter called "Information") is provided
* free of charge for the sole purpose to support your application work.
* The Software and Information is subject to the following
* terms and conditions:
*
* The Software is specifically designed for the exclusive use for
* Bosch Sensortec products by personnel who have special experience
* and training. Do not use this Software if you do not have the
* proper experience or training.
*
* This Software package is provided `` as is `` and without any expressed
* or implied warranties,including without limitation, the implied warranties
* of merchantability and fitness for a particular purpose.
*
* Bosch Sensortec and their representatives and agents deny any liability
* for the functional impairment
* of this Software in terms of fitness, performance and safety.
* Bosch Sensortec and their representatives and agents shall not be liable
* for any direct or indirect damages or injury, except as
* otherwise stipulated in mandatory applicable law.
*
* The Information provided is believed to be accurate and reliable.
* Bosch Sensortec assumes no responsibility for the consequences of use
* of such Information nor for any infringement of patents or
* other rights of third parties which may result from its use.
* No license is granted by implication or otherwise under any patent or
* patent rights of Bosch. Specifications mentioned in the Information are
* subject to change without notice.
**************************************************************************/
/*! \file bme680_calculations.h
 \brief BME680 Sensor Driver calculation Header File */

/*************************************************************************/
#ifndef __BME680_CALCULATIONS_H__
#define __BME680_CALCULATIONS_H__

#ifdef __cplusplus
extern "C"
{
#endif

/***************************************************************************
 Header files
 ****************************************************************************/
#include "bme680.h"

/***************************************************************************
 Macros, Enums, Constants
 ****************************************************************************/

/***************************************************************************
 Module globals, typedefs
 ****************************************************************************/

/***************************************************************************
 Function definitions
 ****************************************************************************/
/* bme680_calculations.h */
#ifdef	FIXED_POINT_COMPENSATION
/**************************************************************/
/**\name	FUNCTION FOR INTEGER OUTPUT GAS*/
/**************************************************************/
/*!
 * @brief This function is used to convert uncompensated gas data to
 * compensated gas data using compensation formula(integer version)
 */
s32 bme680_calculate_gas_int32(u16 gas_adc_u16, u8 gas_range_u8,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION FOR INTEGER OUTPUT TEMPERATURE*/
/**************************************************************/
/*!
 * @brief This function is used to convert the uncompensated
 * temperature data to compensated temperature data using
 * compensation formula(integer version)
 *
 * @note Returns the value in 0.01 degree Centigrade
 * Output value of "5123" equals 51.23 DegC.
 */
s32 bme680_compensate_temperature_int32(u32 v_uncomp_temperature_u32,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION FOR INTEGER OUTPUT HUMIDITY*/
/**************************************************************/
/*!
 * @brief This function is used to convert the uncompensated
 * humidity data to compensated humidity data using
 * compensation formula(integer version)
 *
 * @note Returns the value in %rH as unsigned 32bit integer
 * in Q22.10 format(22 integer 10 fractional bits).
 * @note An output value of 42313 represents 42313 / 1024 = 41.321 %rH
 */
s32 bme680_compensate_humidity_int32(u32 v_uncomp_humidity_u32,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION FOR INTEGER OUTPUT PRESSURE*/
/**************************************************************/
/*!
 * @brief This function is used to convert the uncompensated
 * pressure data to compensated pressure data data using
 * compensation formula(integer version)
 *
 * @note Returns the value in Pascal(Pa)
 * Output value of "96386" equals 96386 Pa = 963.86 hPa = 963.86 millibar
 */
s32 bme680_compensate_pressure_int32(u32 v_uncomp_pressure_u32,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION FOR INTEGER TEMPERATURE-RESISTANCE*/
/**************************************************************/
/*!
 * @brief This function is used to convert temperature to resistance
 * using the integer compensation formula
 */
u8 bme680_convert_temperature_to_resistance_int32(u16 heater_temp_u16,
	s16 ambient_temp_s16, struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION TO CONVERT INT32_H to U16_H BIT OPUTPUT*/
/**************************************************************/
/*!
 * @brief Reads actual humidity from uncompensated humidity
 *
 * @note Returns the value in %rH as unsigned 16bit integer
 * @note An output value of 42313 represents 42313/512 = 82.643 %rH
 */
u16 bme680_compensate_H_int32_sixteen_bit_output(u32 v_uncomp_humidity_u32,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION TO CONVERT INT32_T to S16_T BIT OPUTPUT*/
/**************************************************************/
/*!
 * @brief Reads actual temperature from uncompensated temperature
 *
 * @note Returns the value with 500LSB/DegC centred around 24 DegC
 * output value of "5123" equals(5123/500)+24 = 34.246DegC
 */
s16 bme680_compensate_T_int32_sixteen_bit_output(u32 v_uncomp_temperature_u32,
	struct bme680_t *bme680);
/**************************************************************/
/**\name	FUNCTION TO CONVERT INT32_P to U24_P BIT OPUTPUT*/
/**************************************************************/
/*!
 * @brief Reads actual pressure from uncompensated pressure in Pa.
 *
 * @note Output value of "12337434" represents
 * 12337434 / 128 = 96386.2 Pa = 963.862 hPa
 */
u32 bme680_compensate_P_int32_twentyfour_bit_output(u32 v_uncomp_pressure_u32,
	struct bme680_t *bme680);

#else
/**************************************************************/
/**\name	FUNCTION FOR FLOAT OUTPUT GAS */
/**************************************************************/
/*!
 * @brief This function is used to convert uncompensated gas data to
 * compensated gas data using compensation formula
 */
double bme680_compensate_gas_double(u16 gas_adc_u16, u8 gas_range_u8,
	struct bme680_t *bme680);

/**************************************************************/
/**\name	FUNCTION FOR FLOAT OUTPUT HUMIDITY */
/**************************************************************/

/*!
 * @brief This function is used to convert the uncompensated
 * humidity data to compensated humidity data data using
 * compensation formula
 *
 * @note returns the value in relative humidity (%rH)
 * @note Output value of "42.12" equals 42.12 %rH
 */
double bme680_compensate_humidity_double(u16 uncom_humidity_u16,
	double comp_temperature, struct bme680_t *bme680);

/**************************************************************/
/**\name	FUNCTION FOR FLOAT OUTPUT PRESSURE*/
/**************************************************************/
/*!
 * @brief This function is used to convert the uncompensated
 * pressure data to compensated data using compensation formula
 *
 * @note Returns pressure in Pa as double.
 * @note Output value of "96386.2" equals 96386.2 Pa = 963.862 hPa.
 */
double bme680_compensate_pressure_double(u32 uncom_pressure_u32,
	struct bme680_t *bme680);

/**************************************************************/
/**\name	FUNCTION FOR FLOAT OUTPUT TEMPERATURE*/
/**************************************************************/

/*!
 * @brief This function used to convert temperature data
 * to uncompensated temperature data using compensation formula
 *
 * @note returns the value in Degree centigrade
 * @note Output value of "51.23" equals 51.23 DegC.
 */
double bme680_compensate_temperature_double(u32 uncom_temperature_u32,
	struct bme680_t *bme680);

/**************************************************************/
/**\name	FUNCTION FOR TEMPERATURE TO RESISTANCE */
/**************************************************************/

/*!
 * @brief This function is used to convert temperature to resistance
 * using the compensation formula
 */
double bme680_convert_temperature_to_resistance_double(u16 heater_temp_u16,
	s16 ambient_temp_s16, struct bme680_t *bme680);
#endif
/* bme680_calculations.h */

#ifdef __cplusplus
}
#endif

#endif
