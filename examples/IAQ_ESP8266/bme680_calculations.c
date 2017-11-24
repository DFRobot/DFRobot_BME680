/**
*
****************************************************************************
* Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
*
* File : bme680_calculations.c
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
/*! \file bme680_calculations.c
    \brief BME680 Sensor Driver calculation source File */

/***************************************************************************
	Header files
****************************************************************************/
#include "bme680_calculations.h"


/***************************************************************************
	Macros, Enums, Constants
****************************************************************************/


/***************************************************************************
	File globals, typedefs
****************************************************************************/


/***************************************************************************
	Function definitions
****************************************************************************/
/* bme680.c */
#ifdef FIXED_POINT_COMPENSATION
/*!
 *	@brief This function is used to convert uncompensated gas data to
 *	compensated gas data using compensation formula(integer version)
 *
 *	@param gas_adc_u16: The value of gas resistance calculated
 *       using temperature
 *	@param gas_range_u8: The value of gas range form register value
 *	@param bme680: structure pointer.
 *
 *	@return calculated compensated gas from compensation formula
 *	@retval compensated gas data
 *
 *
*/
s32 bme680_calculate_gas_int32(u16 gas_adc_u16, u8 gas_range_u8,
	struct bme680_t *bme680)
{
	s8 range_switching_error_val = 0;
	s64 var1 = 0;
	s64 var2 = 0;
	s32 gas_res = 0;



	const u64 lookup_k1_range[BME680_GAS_RANGE_RL_LENGTH] = {
	2147483647UL, 2147483647UL, 2147483647UL, 2147483647UL, 2147483647UL,
	2126008810UL, 2147483647UL, 2130303777UL, 2147483647UL, 2147483647UL,
	2143188679UL, 2136746228UL, 2147483647UL, 2126008810UL, 2147483647UL,
	2147483647UL};

	const u64 lookup_k2_range[BME680_GAS_RANGE_RL_LENGTH] = {
	4096000000UL, 2048000000UL, 1024000000UL, 512000000UL,
	255744255UL, 127110228UL, 64000000UL, 32258064UL, 16016016UL,
	8000000UL, 4000000UL, 2000000UL, 1000000UL, 500000UL, 250000UL,
	125000UL};



		range_switching_error_val =
		bme680->cal_param.range_switching_error;


	var1 = (s64)((1340 + (5 * (s64)range_switching_error_val)) *
		((s64)lookup_k1_range[gas_range_u8])) >> 16;
	var2 = (s64)((s64)gas_adc_u16 << 15) - (s64)(1 << 24) + var1;
	#ifndef __KERNEL__
	gas_res = (s32)(((((s64)lookup_k2_range[gas_range_u8] *
		(s64)var1) >> 9) + (var2 >> 1)) / var2);
	#else
	gas_res = (s32)(div64_s64(((((s64)lookup_k2_range[gas_range_u8] *
		(s64)var1) >> 9) + (var2 >> 1)), var2));
	#endif
	return gas_res;
}
/*!
 *	@brief This function is used to convert the uncompensated
 *	temperature data to compensated temperature data using
 *	compensation formula(integer version)
 *	@note Returns the value in 0.01 degree Centigrade
 *	Output value of "5123" equals 51.23 DegC.
 *
 *
 *
 *  @param  v_uncomp_temperature_u32 : value of uncompensated temperature
 *	@param bme680: structure pointer.
 *
 *  @return Returns the compensated temperature data
 *
*/
s32 bme680_compensate_temperature_int32(u32 v_uncomp_temperature_u32,
	struct bme680_t *bme680)
{
	s32 var1 = 0;
	s32 var2 = 0;
	s32 var3 = 0;
	s32 temp_comp = 0;

	var1 = ((s32)v_uncomp_temperature_u32 >> 3) -
		((s32)bme680->cal_param.par_T1 << 1);
	var2 = (var1 * (s32)bme680->cal_param.par_T2) >> 11;
	var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) *
		((s32)bme680->cal_param.par_T3 << 4)) >> 14;
	bme680->cal_param.t_fine = var2 + var3;
	temp_comp = ((bme680->cal_param.t_fine * 5) + 128) >> 8;

	return temp_comp;

}

/*!
 *	@brief This function is used to convert the uncompensated
 *	humidity data to compensated humidity data using
 *	compensation formula(integer version)
 *
 *	@note Returns the value in %rH as unsigned 32bit integer
 *	in Q22.10 format(22 integer 10 fractional bits).
 *	@note An output value of 42313
 *	represents 42313 / 1024 = 41.321 %rH
 *
 *
 *
 *  @param  v_uncomp_humidity_u32: value of uncompensated humidity
 *	@param bme680: structure pointer.
 *
 *  @return Return the compensated humidity data
 *
*/
s32 bme680_compensate_humidity_int32(u32 v_uncomp_humidity_u32,
	struct bme680_t *bme680)
{
	s32 temp_scaled = 0;
	s32 var1	= 0;
	s32 var2	= 0;
	s32 var3	= 0;
	s32 var4	= 0;
	s32 var5	= 0;
	s32 var6	= 0;
	s32 humidity_comp = 0;

	temp_scaled = (((s32)bme680->cal_param.t_fine * 5) + 128) >> 8;
	var1 = (s32)v_uncomp_humidity_u32 -
		((s32)((s32)bme680->cal_param.par_H1 << 4)) -
		(((temp_scaled * (s32)bme680->cal_param.par_H3) /
		((s32)100)) >> 1);

	var2 = ((s32)bme680->cal_param.par_H2 *
		(((temp_scaled * (s32)bme680->cal_param.par_H4) /
		((s32)100)) + (((temp_scaled *
		((temp_scaled * (s32)bme680->cal_param.par_H5) /
		((s32)100))) >> 6) / ((s32)100)) + (s32)(1 << 14))) >> 10;

	var3 = var1 * var2;

	var4 = ((((s32)bme680->cal_param.par_H6) << 7) +
		((temp_scaled * (s32)bme680->cal_param.par_H7) /
		((s32)100))) >> 4;

	var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
	var6 = (var4 * var5) >> 1;

	humidity_comp = (var3 + var6) >> 12;
	if (humidity_comp > BME680_MAX_HUMIDITY_VALUE)
		humidity_comp = BME680_MAX_HUMIDITY_VALUE;
	else if (humidity_comp < BME680_MIN_HUMIDITY_VALUE)
		humidity_comp = BME680_MIN_HUMIDITY_VALUE;

	return humidity_comp;
}


/*!
 * @brief This function is used to convert the uncompensated
 *	pressure data to compensated pressure data data using
 *	compensation formula(integer version)
 *
 * @note Returns the value in Pascal(Pa)
 * Output value of "96386" equals 96386 Pa =
 * 963.86 hPa = 963.86 millibar
 *
 *
 *
 *  @param v_uncomp_pressure_u32 : value of uncompensated pressure
 *	@param bme680: structure pointer.
 *
 *  @return Return the compensated pressure data
 *
*/
s32 bme680_compensate_pressure_int32(u32 v_uncomp_pressure_u32,
	struct bme680_t *bme680)
{
	s32 var1 = 0;
	s32 var2 = 0;
	s32 var3 = 0;
	s32 var4 = 0;
	s32 pressure_comp = 0;

	var1 = (((s32)bme680->cal_param.t_fine) >> 1) - 64000;
	var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) *
		(s32)bme680->cal_param.par_P6) >> 2;
	var2 = var2 + ((var1 * (s32)bme680->cal_param.par_P5) << 1);
	var2 = (var2 >> 2) + ((s32)bme680->cal_param.par_P4 << 16);
	var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) *
		((s32)bme680->cal_param.par_P3 << 5)) >> 3) +
		(((s32)bme680->cal_param.par_P2 * var1) >> 1);
	var1 = var1 >> 18;
	var1 = ((32768 + var1) * (s32)bme680->cal_param.par_P1) >> 15;
	pressure_comp = 1048576 - v_uncomp_pressure_u32;
	pressure_comp = (s32)((pressure_comp - (var2 >> 12)) * ((u32)3125));
	var4 = (1 << 31);
	if (pressure_comp >= var4)
		pressure_comp = ((pressure_comp / (u32)var1) << 1);
	else
		pressure_comp = ((pressure_comp << 1) / (u32)var1);
	var1 = ((s32)bme680->cal_param.par_P9 * (s32)(((pressure_comp >> 3) *
		(pressure_comp >> 3)) >> 13)) >> 12;
	var2 = ((s32)(pressure_comp >> 2) *
		(s32)bme680->cal_param.par_P8) >> 13;
	var3 = ((s32)(pressure_comp >> 8) * (s32)(pressure_comp >> 8) *
		(s32)(pressure_comp >> 8) *
		(s32)bme680->cal_param.par_P10) >> 17;

	pressure_comp = (s32)(pressure_comp) + ((var1 + var2 + var3 +
		((s32)bme680->cal_param.par_P7 << 7)) >> 4);

	return pressure_comp;
}
/*!
 *	@brief This function is used to convert temperature to resistance
 *	using the integer compensation formula
 *
 *	@param heater_temp_u16: The value of heater temperature
 *	@param ambient_temp_s16: The value of ambient temperature
 *	@param bme680: structure pointer.
 *
 *	@return calculated resistance from temperature
 *
 *
 *
*/
u8 bme680_convert_temperature_to_resistance_int32(u16 heater_temp_u16,
	s16 ambient_temp_s16, struct bme680_t *bme680)
{
	s32 var1 = 0;
	s32 var2 = 0;
	s32 var3 = 0;
	s32 var4 = 0;
	s32 var5 = 0;
	s32 res_heat_x100 = 0;
	u8 res_heat = 0;


	if ((heater_temp_u16 >= BME680_GAS_PROFILE_TEMPERATURE_MIN)
	&& (heater_temp_u16 <= BME680_GAS_PROFILE_TEMPERATURE_MAX)) {

		var1 = (((s32)ambient_temp_s16 *
			bme680->cal_param.par_GH3) / 10) << 8;
		var2 = (bme680->cal_param.par_GH1 + 784) *
			(((((bme680->cal_param.par_GH2 + 154009) *
			heater_temp_u16 * 5) / 100) + 3276800) / 10);
		var3 = var1 + (var2 >> 1);
		var4 = (var3 / (bme680->cal_param.res_heat_range + 4));

		var5 = (131 * bme680->cal_param.res_heat_val) + 65536;

		res_heat_x100 = (s32)(((var4 / var5) - 250) * 34);
		res_heat = (u8) ((res_heat_x100 + 50) / 100);

	}
	return res_heat;
}
/*!
 * @brief Reads actual humidity from uncompensated humidity
 * @note Returns the value in %rH as unsigned 16bit integer
 * @note An output value of 42313
 * represents 42313/512 = 82.643 %rH
 *
 *
 *
 *  @param v_uncomp_humidity_u32: value of uncompensated humidity
 *	@param bme680: structure pointer.
 *
 *  @return Return the actual relative humidity output as u16
 *
*/
u16 bme680_compensate_H_int32_sixteen_bit_output(u32 v_uncomp_humidity_u32,
	struct bme680_t *bme680)
{
	u32 v_x1_u32 = 0;
	u16 v_x2_u32 = 0;

	v_x1_u32 = (u32) bme680_compensate_humidity_int32(
	v_uncomp_humidity_u32, bme680);
	v_x2_u32 = (u16)(v_x1_u32 >> 1);
	return v_x2_u32;
}

/*!
 * @brief Reads actual temperature from uncompensated temperature
 * @note Returns the value with 500LSB/DegC centred around 24 DegC
 * output value of "5123" equals(5123/500)+24 = 34.246DegC
 *
 *
 *  @param v_uncomp_temperature_u32: value of uncompensated temperature
 *	@param bme680: structure pointer.
 *
 *
 *  @return Return the actual temperature as s16 output
 *
*/
s16 bme680_compensate_T_int32_sixteen_bit_output(u32 v_uncomp_temperature_u32,
	struct bme680_t *bme680)
{
	s16 temperature = 0;

	bme680_compensate_temperature_int32(v_uncomp_temperature_u32, bme680);
	temperature  = (s16)((((
		bme680->cal_param.t_fine - 122880) * 25) + 128) >> 8);

	return temperature;
}

/*!
 * @brief Reads actual pressure from uncompensated pressure
 * @note Returns the value in Pa.
 * @note Output value of "12337434"
 * @note represents 12337434 / 128 = 96386.2 Pa = 963.862 hPa
 *
 *
 *
 *  @param v_uncomp_pressure_u32 : value of uncompensated pressure
 *	@param bme680: structure pointer.
 *
 *  @return the actual pressure in u32
 *
*/
u32 bme680_compensate_P_int32_twentyfour_bit_output(u32 v_uncomp_pressure_u32,
	struct bme680_t *bme680)
{
	u32 pressure = 0;

	pressure = (u32)bme680_compensate_pressure_int32(
		v_uncomp_pressure_u32, bme680);
	pressure = (u32)(pressure >> 1);
	return pressure;
}
#else
/*!
 *	@brief This function is used to convert uncompensated gas data to
 *	compensated gas data using compensation formula
 *
 *	@param gas_adc_u16: The value of gas resistance calculated
 *       using temperature
 *	@param gas_range_u8: The value of gas range form register value
 *	@param bme680: structure pointer.
 *
 *	@return calculated compensated gas from compensation formula
 *	@retval compensated gas
 *
 *
*/

double bme680_compensate_gas_double(u16 gas_adc_u16, u8 gas_range_u8,
	struct bme680_t *bme680)
{
	double gas_res_d = 0;


#ifdef HEATER_C1_ENABLE

	const double lookup_k1_range[BME680_GAS_RANGE_RL_LENGTH] = {
	0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -0.8,
	0.0, 0.0, -0.2, -0.5, 0.0, -1.0, 0.0, 0.0};
	const double lookup_k2_range[BME680_GAS_RANGE_RL_LENGTH] = {
	0.0, 0.0, 0.0, 0.0, 0.1, 0.7, 0.0, -0.8,
	-0.1, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	s8 range_switching_error_val = 0;
	double var1 = 0;
	double var2 = 0;
	double var3 = 0;



	range_switching_error_val =
	bme680->cal_param.range_switching_error;


	var1 = (1340.0 + (5.0 * range_switching_error_val));
	var2 = (var1) * (1.0 + lookup_k1_range[gas_range_u8]/100.0);
	var3 = 1.0 + (lookup_k2_range[gas_range_u8]/100.0);

	gas_res_d = 1.0 / (double)(var3 * (0.000000125) *
		(double)(1 << gas_range_u8)
		* (((((double)gas_adc_u16) - 512.00)/var2) + 1.0));

#else
	gas_res_d = 1.0 / ((0.000000125) * (double)(1 << gas_range_u8) *
		((((double)(gas_adc_u16) - 512.00) / 1365.3333) + 1.0));
#endif
	return gas_res_d;
}


/*!
 * @brief This function is used to convert the uncompensated
 *	humidity data to compensated humidity data data using
 *	compensation formula
 * @note returns the value in relative humidity (%rH)
 * @note Output value of "42.12" equals 42.12 %rH
 *
 *  @param uncom_humidity_u16 : value of uncompensated humidity
 *  @param comp_temperature   : value of compensated temperature
 *	@param bme680: structure pointer.
 *
 *
 *  @return Return the compensated humidity data in floating point
 *
*/
double bme680_compensate_humidity_double(u16 uncom_humidity_u16,
	double comp_temperature, struct bme680_t *bme680)
{
	double humidity_comp = 0;
	double var1 = 0;
	double var2 = 0;
	double var3 = 0;
	double var4 = 0;

	var1 = (double)((double)uncom_humidity_u16) - (((double)
	bme680->cal_param.par_H1 * 16.0) +
		(((double)bme680->cal_param.par_H3 / 2.0)
		* comp_temperature));

	var2 = var1 * ((double)(
		((double) bme680->cal_param.par_H2 / 262144.0)
		*(1.0 + (((double)bme680->cal_param.par_H4 / 16384.0)
		* comp_temperature) + (((double)bme680->cal_param.par_H5
		/ 1048576.0) * comp_temperature
		* comp_temperature))));
	var3 = (double) bme680->cal_param.par_H6 / 16384.0;
	var4 = (double) bme680->cal_param.par_H7 / 2097152.0;

	humidity_comp = var2 +
	((var3 + (var4 * comp_temperature)) * var2 * var2);
	if (humidity_comp > BME680_MAX_HUMIDITY_VALUE)
		humidity_comp = BME680_MAX_HUMIDITY_VALUE;
	else if (humidity_comp < BME680_MIN_HUMIDITY_VALUE)
		humidity_comp = BME680_MIN_HUMIDITY_VALUE;
	return humidity_comp;
}

/*!
 * @brief This function is used to convert the uncompensated
 * pressure data to compensated data using compensation formula
 * @note Returns pressure in Pa as double.
 * @note Output value of "96386.2"
 * equals 96386.2 Pa = 963.862 hPa.
 *
 *
 *  @param uncom_pressure_u32 : value of uncompensated pressure
 *	@param bme680: structure pointer.
 *
 *  @return  Return the compensated pressure data in floating point
 *
*/
double bme680_compensate_pressure_double(u32 uncom_pressure_u32,
	struct bme680_t *bme680)
{
	double data1_d = 0;
	double data2_d = 0;
	double data3_d = 0;
	double pressure_comp = 0;

	data1_d = (((double)bme680->cal_param.t_fine / 2.0) - 64000.0);
	data2_d = data1_d * data1_d * (((double)bme680->cal_param.par_P6) /
		(131072.0));
	data2_d = data2_d + (data1_d * ((double)bme680->cal_param.par_P5) *
		2.0);
	data2_d = (data2_d / 4.0) + (((double)bme680->cal_param.par_P4) *
		65536.0);
	data1_d = (((((double)bme680->cal_param.par_P3 * data1_d
		* data1_d) / 16384.0) + ((double)bme680->cal_param.par_P2
		* data1_d)) / 524288.0);
	data1_d = ((1.0 + (data1_d / 32768.0)) *
		((double)bme680->cal_param.par_P1));
	pressure_comp = (1048576.0 - ((double)uncom_pressure_u32));
	/* Avoid exception caused by division by zero */
	if ((int)data1_d != 0) {
		pressure_comp = (((pressure_comp - (data2_d
			/ 4096.0)) * 6250.0) / data1_d);
		data1_d = (((double)bme680->cal_param.par_P9) *
			pressure_comp * pressure_comp) /  2147483648.0;
		data2_d = pressure_comp * (((double)bme680->cal_param.par_P8)
			/ 32768.0);
		data3_d = ((pressure_comp / 256.0) * (pressure_comp / 256.0) *
			(pressure_comp / 256.0) *
			(bme680->cal_param.par_P10 / 131072.0));
		pressure_comp = (pressure_comp + (data1_d + data2_d + data3_d +
			((double)bme680->cal_param.par_P7 * 128.0)) / 16.0);
		return pressure_comp;

	} else {
		return 0;
	}


}

/*!
 * @brief This function used to convert temperature data
 *	to uncompensated temperature data using compensation formula
 * @note returns the value in Degree centigrade
 * @note Output value of "51.23" equals 51.23 DegC.
 *
 *  @param uncom_temperature_u32 : value of uncompensated temperature
 *	@param bme680: structure pointer.
 *
 *  @return  Return the actual temperature in floating point
 *
*/
double bme680_compensate_temperature_double(u32 uncom_temperature_u32,
	struct bme680_t *bme680)
{
	double data1_d = 0;
	double data2_d = 0;
	double temperature = 0;
	/* calculate x1 data */
	data1_d  = ((((double)uncom_temperature_u32 / 16384.0)
		- ((double)bme680->cal_param.par_T1 / 1024.0))
		* ((double)bme680->cal_param.par_T2));
	/* calculate x2 data */
	data2_d  = (((((double)uncom_temperature_u32 / 131072.0) -
		((double)bme680->cal_param.par_T1 / 8192.0)) *
		(((double)uncom_temperature_u32 / 131072.0) -
		((double)bme680->cal_param.par_T1 / 8192.0))) *
		((double)bme680->cal_param.par_T3 * 16.0));
	/* t fine value*/
	bme680->cal_param.t_fine = (s32)(data1_d + data2_d);
	/* compensated temperature data*/
	temperature  = ((data1_d + data2_d) /
		5120.0);


	return temperature;
}


/*!
 *	@brief This function is used to convert temperature to resistance
 *	using the compensation formula
 *
 *	@param heater_temp_u16: The value of heater temperature
 *	@param ambient_temp_s16: The value of ambient temperature
 *	@param bme680: structure pointer.
 *
 *	@return calculated resistance from temperature
 *
 *
 *
*/
double bme680_convert_temperature_to_resistance_double(u16 heater_temp_u16,
	s16 ambient_temp_s16, struct bme680_t *bme680)
{
	double var1 = 0;
	double var2 = 0;
	double var3 = 0;
	double var4 = 0;
	double var5 = 0;
	double res_heat = 0;

	if ((heater_temp_u16 >= BME680_GAS_PROFILE_TEMPERATURE_MIN)
	&& (heater_temp_u16 <= BME680_GAS_PROFILE_TEMPERATURE_MAX)) {
#ifdef	HEATER_C1_ENABLE
		var1 = (((double)bme680->cal_param.par_GH1 / (16.0)) + 49.0);
		var2 = ((((double)bme680->cal_param.par_GH2
			/(32768.0)) * (0.0005)) + 0.00235);
#endif
		var3 = ((double)bme680->cal_param.par_GH3 / (1024.0));
		var4 = (var1 * (1.0 + (var2 * (double)heater_temp_u16)));
		var5 = (var4 + (var3 * (double)ambient_temp_s16));

#ifdef	HEATER_C1_ENABLE
		res_heat = (u8)(3.4 * ((var5 *
			(4 / (4 + (double)bme680->cal_param.res_heat_range)) *
			(1/(1 + ((double)bme680->cal_param.res_heat_val
			* 0.002)))) - 25));
#else
		res_heat = (((var5 * (4.0 /
			(4.0 + (double)bme680->cal_param.res_heat_range)))
			- 25.0) * 3.4);
#endif

	}
	return (u8)res_heat;
}

#endif
/* bme680.c */
