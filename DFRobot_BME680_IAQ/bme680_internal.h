/**
*
****************************************************************************
* Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
*
* File : bme680_internal.h
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
/*! \file bme680_internal.h
    \brief BME680 Sensor Driver internal support Header File */

#ifndef _BME680_INTERNAL_H
#define _BME680_INTERNAL_H

/***************************************************************************
	Header files
****************************************************************************/




/***************************************************************************
	Macros Enums, Constants only sensor Specific constants
****************************************************************************/
/* bme680_internal.h */
/* Pre-processor switch for separating between I2C and SPI addresses */

#define BME680_CALIB_SPI_ADDR_1				(0x09)
#define BME680_CALIB_SPI_ADDR_2				(0x61)
#define BME680_PAGE0_SPI_ID_REG				(0x50)

#define BME680_CALIB_I2C_ADDR_1				(0x89)
#define BME680_CALIB_I2C_ADDR_2				(0xE1)
#define BME680_PAGE0_I2C_ID_REG				(0xD0)

#define BME680_OVERSAMP_TEMP_SHIFT			(0x03)
#define BME680_GAS_WAIT_STEP_SIZE			(477)

#define BME680_SENS_CONF_LEN				(0x06)
#define BME680_SENS_HEATR_CONF_LEN			(0x15)

#define BME680_TRUE					(1)
#define BME680_FALSE					(0)

#define BME680_CALIB_PARAM_SIZE				((u8)41)
#define BME680_PAGE0_INTERFACE_SPI			((u8)0)
#define BME680_PAGE1_INTERFACE_SPI			((u8)1)
#define BME680_CALIB_DATA_LENGTH_GAS			(25)
#define BME680_CALIB_DATA_LENGTH			(16)
#define	BME680_BIT_MASK_H1_DATA				(0x0F)
#define	BME680_FIELD_ZERO				(0)
#define	BME680_FIELD_ONE				(1)
#define	BME680_FIELD_TWO				(2)
#define BME680_FIELD_ONE_OFFSET				(17)
#define BME680_FIELD_TWO_OFFSET				(34)
#define BME680_FIELD_SIZE				(17)

/* Sensor Specific constants */
#define	BME680_GAS_BIT_MASK				(0x00C0)
#define	BME680_GAS_WAIT_MAX_TIMER_VALUE			(0x3F)
#define	BME680_GAS_WAIT_MIN_TIMER_VALUE			(0x00)

#define BME680_PROFILE_MAX				(10)


#define BME680_ADDR_SPI_MEM_PAGE			(0x73)
#define BME680_ADDR_OP_MODE				(0x74)
#define BME680_ADDR_SENS_CONF_START			(0x5A)
#define BME680_ADDR_FIELD_0				(0x1D)
#define BME680_ADDR_SENSOR_CONFIG			(0x70)
#define BME680_ADDR_RES_HEAT_VAL			(0x00)
#define BME680_ADDR_RES_HEAT_RANGE			(0x02)
#define BME680_ADDR_RANGE_SWITCHING_ERR			(0x04)

/* Section 3.2: Sub-register addresses, masks and bit shifts */

#define BME680_MASK_OP_MODE				(0xFC)
#define BME680_MASK_HEATR_CTRL				(0xF7)
#define BME680_MASK_ODR_3				(0x7F)
#define BME680_MASK_ODR_2_0				(0x1F)
#define BME680_MASK_RUN_GAS				(0xEF)
#define BME680_MASK_PROF_INDEX				(0xF0)
#define BME680_MASK_OSRS_HUM				(0xF8)
#define BME680_MASK_OSRS_PRES				(0xE3)
#define BME680_MASK_OSRS_TEMP				(0x1F)
#define BME680_MASK_FILTER				(0xE3)
#define BME680_MASK_NEW_DATA				(0x7F)
#define BME680_MASK_GAS_MEAS_STAT			(0xBF)
#define BME680_MASK_TPHG_MEAS_STAT			(0xDF)
#define BME680_MASK_GAS_MEAS_INDEX			(0xF0)
#define BME680_MASK_GAS_RANGE				(0xF0)
#define BME680_MASK_GAS_VALID				(0xDF)
#define BME680_MASK_HEATR_STAB				(0xEF)
#define BME680_MASK_SPI_3W_INT				(0xBF)
#define BME680_MASK_SPI_3W_EN				(0xFE)
#define BME680_MASK_MEM_PAGE				(0xEF)
#define BME680_MASK_RES_HEAT_RANGE			(0xCF)
#define BME680_MASK_RANGE_ERR				(0x0F)

/* Section : Register settings/values */
/* Lengths to support burst reads/writes */

#define BME680_SINGLE_FIELD_LENGTH			(15)
#define BME680_LEN_ALL_FIELD_SIZE			(49)


#define BME680_ADDR_FIELD_0_STATUS			(0x1D)
#define BME680_ADDR_FIELD_1_STATUS			(0x2E)
#define BME680_ADDR_FIELD_2_STATUS			(0x3F)
#define BME680_ADDR_FIELD_0_TEMP1			(0x22)
#define BME680_ADDR_FIELD_0_TEMP2			(0x27)
#define BME680_ADDR_FIELD_1_TEMP1			(0x33)
#define BME680_ADDR_FIELD_1_TEMP2			(0x38)
#define BME680_ADDR_FIELD_2_TEMP1			(0x44)
#define BME680_ADDR_FIELD_2_TEMP2			(0x49)
#define BME680_ADDR_FIELD_0_PRESS			(0x1F)
#define BME680_ADDR_FIELD_1_PRESS			(0x30)
#define BME680_ADDR_FIELD_2_PRESS			(0x41)
#define BME680_ADDR_FIELD_0_HUM				(0x25)
#define BME680_ADDR_FIELD_1_HUM				(0x36)
#define BME680_ADDR_FIELD_2_HUM				(0x47)
#define BME680_ADDR_FIELD_0_GAS				(0x2A)
#define BME680_ADDR_FIELD_1_GAS				(0x3B)
#define BME680_ADDR_FIELD_2_GAS				(0x4C)


/*******************************************************/
/* Array Index to Field data mapping*/
/********************************************************/
/* For Calibration Data*/

#define DIG_T2_LSB_REG					(1)
#define DIG_T2_MSB_REG					(2)
#define DIG_T3_REG					(3)
#define DIG_P1_LSB_REG					(5)
#define DIG_P1_MSB_REG					(6)
#define DIG_P2_LSB_REG					(7)
#define DIG_P2_MSB_REG					(8)
#define DIG_P3_REG					(9)
#define DIG_P4_LSB_REG					(11)
#define DIG_P4_MSB_REG					(12)
#define DIG_P5_LSB_REG					(13)
#define DIG_P5_MSB_REG					(14)
#define DIG_P7_REG					(15)
#define DIG_P6_REG					(16)
#define DIG_P8_LSB_REG					(19)
#define DIG_P8_MSB_REG					(20)
#define DIG_P9_LSB_REG					(21)
#define DIG_P9_MSB_REG					(22)
#define DIG_P10_REG					(23)
#define DIG_H2_MSB_REG					(25)
#define DIG_H2_LSB_REG					(26)
#define DIG_H1_LSB_REG					(26)
#define DIG_H1_MSB_REG					(27)
#define DIG_H3_REG					(28)
#define DIG_H4_REG					(29)
#define DIG_H5_REG					(30)
#define DIG_H6_REG					(31)
#define DIG_H7_REG					(32)
#define DIG_T1_LSB_REG					(33)
#define DIG_T1_MSB_REG					(34)
#define DIG_GH2_LSB_REG					(35)
#define DIG_GH2_MSB_REG					(36)
#define DIG_GH1_REG					(37)
#define DIG_GH3_REG					(38)

/* For TPHG data */

#define FIELD_0_MEAS_STATUS_0				(0)
#define FIELD_0_MEAS_STATUS_1				(1)
#define FIELD_0_GAS_RL_LSB				(14)

/*!
@brief data frame includes temperature, pressure, humidity
and gas data*/
#define	BME680_DATA_FRAME_PRESSURE_MSB_DATA		((u8)2)
#define	BME680_DATA_FRAME_PRESSURE_LSB_DATA		((u8)3)
#define	BME680_DATA_FRAME_PRESSURE_XLSB_DATA		((u8)4)
#define	BME680_DATA_FRAME_TEMPERATURE1_MSB_DATA		((u8)5)
#define	BME680_DATA_FRAME_TEMPERATURE1_LSB_DATA		((u8)6)
#define	BME680_DATA_FRAME_TEMPERATURE1_XLSB_DATA	((u8)7)
#define	BME680_DATA_FRAME_HUMIDITY_MSB_DATA		((u8)8)
#define	BME680_DATA_FRAME_HUMIDITY_LSB_DATA		((u8)9)
#define	BME680_DATA_FRAME_GAS_MSB_DATA			((u8)13)
#define	BME680_DATA_FRAME_GAS_LSB_DATA			((u8)14)


/* Positions to support indexing in an array */
#define BME680_INDEX_CTRL_GAS_0				(0)
#define BME680_INDEX_CTRL_GAS_1				(1)
#define BME680_INDEX_CTRL_HUM				(2)
#define BME680_INDEX_CTRL_MEAS				(4)
#define BME680_INDEX_CONFIG				(5)

/* Constants to store the bit shift parameters */
#define BME680_SHIFT_OP_MODE				(0)
#define BME680_SHIFT_HEATR_CTRL				(3)
#define BME680_SHIFT_ODR_3				(4)
#define BME680_SHIFT_ODR_2_0				(5)
#define BME680_SHIFT_RUN_GAS				(4)
#define BME680_SHIFT_PROF_INDEX				(0)
#define BME680_SHIFT_OSRS_HUM				(0)
#define BME680_SHIFT_OSRS_TEMP				(5)
#define	BME680_SHIFT_OSRS_PRES				(2)
#define BME680_SHIFT_FILTER				(2)
#define BME680_SHIFT_NEW_DATA				(7)
#define BME680_SHIFT_GAS_MEAS_STAT			(6)
#define BME680_SHIFT_TPHG_MEAS_STAT			(5)
#define BME680_SHIFT_GAS_MEAS_INDEX			(0)
#define BME680_SHIFT_GAS_RANGE				(0)
#define BME680_SHIFT_GAS_VALID				(5)
#define BME680_SHIFT_HEATR_STAB				(4)
#define BME680_SHIFT_SPI_3W_INT				(6)
#define BME680_SHIFT_SPI_3W_EN				(0)
#define BME680_SHIFT_SPI_MEM_PAGE			(4)
#define BME680_SHIFT_RES_HEAT_RANGE			(4)
#define BME680_SHIFT_RANGE_ERR				(4)

#define BME680_ONE					(1)
#define BME680_TWO					(2)
#define BME680_THREE					(3)

#define BME680_GEN_READ_DATA_LENGTH			((u8)1)
#define BME680_GEN_WRITE_DATA_LENGTH			((u8)1)

/* bme680_internal.h */
/***************************************************************************
	Module globals, typedefs
****************************************************************************/


/***************************************************************************
	Function definitions
****************************************************************************/


#endif
