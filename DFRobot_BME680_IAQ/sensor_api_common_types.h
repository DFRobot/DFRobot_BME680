/**
*
****************************************************************************
* Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
*
* File : sensor_api_common_types.h
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
/*! \file sensor_api_common_types.h
    \brief sensor API common data types Header File */

#ifndef __SENSOR_API_COMMON_TYPES_H__
#define __SENSOR_API_COMMON_TYPES_H__


/***************************************************************************/


/***************************************************************************
	Macros, Enum, Constant
****************************************************************************/
/* sensor_api_common_types.h */
/*!
* @brief The following definition is used for defining the data types
*
* @note While porting the API please consider the following
* @note Please check the version of C standard
* @note Are you using Linux platform
*/

/*!
* @brief For the Linux platform support
* Please use the types.h for your data types definitions
*/
#ifdef	__KERNEL__

#include <linux/types.h>
#include <linux/math64.h>
	/* singed integer type*/
	typedef int8_t s8;/**< used for signed 8bit */
	typedef int16_t s16;/**< used for signed 16bit */
	typedef int32_t s32;/**< used for signed 32bit */
	typedef int64_t s64;/**< used for signed 64bit */

	typedef u_int8_t u8;/**< used for unsigned 8bit */
	typedef u_int16_t u16;/**< used for unsigned 16bit */
	typedef u_int32_t u32;/**< used for unsigned 32bit */
	/*typedef	u_int64_t u64;*//**< used for unsigned 64bit */
	typedef signed long long int s64;
#else /* ! __KERNEL__ */
	/**********************************************************
	* These definitions are used to define the C
	* standard version data types
	***********************************************************/
# if defined(__STDC_VERSION__)
	/************************************************
	 * compiler is C11 C standard
	************************************************/
#if (__STDC_VERSION__ == 201112L)
	/************************************************/
#include <stdint.h>

	/************************************************/
	/*unsigned integer types*/
	typedef uint8_t u8;/**< used for unsigned 8bit */
	typedef uint16_t u16;/**< used for unsigned 16bit */
	typedef uint32_t u32;/**< used for unsigned 32bit */
	typedef uint64_t u64;/**< used for unsigned 64bit */

	/*signed integer types*/
	typedef int8_t s8;/**< used for signed 8bit */
	typedef int16_t s16;/**< used for signed 16bit */
	typedef int32_t s32;/**< used for signed 32bit */
	typedef int64_t s64;/**< used for signed 64bit */
	/*typedef	signed long long int s64;*/
	/************************************************
	 * compiler is C99 C standard
	************************************************/
#elif (__STDC_VERSION__ == 199901L)

	/* stdint.h is a C99 supported c library.
	which is used to fixed the integer size*/
	/************************************************/
#include <stdint.h>
	/************************************************/

	/*unsigned integer types*/
	typedef uint8_t u8;/**< used for unsigned 8bit */
	typedef uint16_t u16;/**< used for unsigned 16bit */
	typedef uint32_t u32;/**< used for unsigned 32bit */
	typedef uint64_t u64;/**< used for unsigned 64bit */

	/*signed integer types*/
	typedef int8_t s8;/**< used for signed 8bit */
	typedef int16_t s16;/**< used for signed 16bit */
	typedef int32_t s32;/**< used for signed 32bit */
	/*typedef	int64_t s64;*//**< used for signed 64bit */

	typedef signed long long int s64;
	/************************************************
	 * compiler is C89 or other C standard
	************************************************/
#else /*  !defined(__STDC_VERSION__) */
	/*!
	* @brief By default it is defined as 32 bit machine configuration
	*	define your data types based on your
	*	machine/compiler/controller configuration
	*/
#define  MACHINE_32_BIT

	/*! @brief
	 *	If your machine support 16 bit
	 *	define the MACHINE_16_BIT
	 */
#ifdef MACHINE_16_BIT
#include <limits.h>
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed long int s32;/**< used for signed 32bit */

#if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
	typedef long int s64;/**< used for signed 64bit */
	typedef unsigned long int u64;/**< used for unsigned 64bit */
#elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
	typedef long long int s64;/**< used for signed 64bit */
	typedef unsigned long long int u64;/**< used for unsigned 64bit */
#else
#warning Either the correct data type for signed 64 bit integer \
	could not be found, or 64 bit integers are not
	supported in your environment.
#warning If 64 bit integers are supported on your platform, \
	please set s64 manually.
#endif

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit */

	/* If your machine support 32 bit
	define the MACHINE_32_BIT*/
#elif defined MACHINE_32_BIT
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed int s32;/**< used for signed 32bit */
	typedef signed long long int s64;/**< used for signed 64bit */

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit */
	typedef unsigned long long int u64;/**< used for unsigned 64bit */

	/* If your machine support 64 bit
	define the MACHINE_64_BIT*/
#elif defined MACHINE_64_BIT
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed int s32;/**< used for signed 32bit */
	typedef signed long int s64;/**< used for signed 64bit */

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit */
	typedef unsigned long int u64;/**< used for unsigned 64bit */

#else
#warning The data types defined above which not supported \
	define the data types manually
#endif
#endif

	/*** This else will execute for the compilers
	 *	which are not supported the C standards
	 *	Like C89/C99/C11***/
#else
	/*!
	* @brief By default it is defined as 32 bit machine configuration
	*	define your data types based on your
	*	machine/compiler/controller configuration
	*/
#define  MACHINE_32_BIT
	/* If your machine support 16 bit
	define the MACHINE_16_BIT*/
#ifdef MACHINE_16_BIT
#include <limits.h>
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed long int s32;/**< used for signed 32bit */

#if defined(LONG_MAX) && LONG_MAX == 0x7fffffffffffffffL
	typedef long int s64;/**< used for signed 64bit */
	typedef unsigned long int u64;/**< used for unsigned 64bit */
#elif defined(LLONG_MAX) && (LLONG_MAX == 0x7fffffffffffffffLL)
	typedef long long int s64;/**< used for signed 64bit */
	typedef unsigned long long int u64;/**< used for unsigned 64bit */
#else
#warning Either the correct data type for signed 64 bit integer \
	could not be found, or 64 bit integers are not
	supported in your environment.
#warning If 64 bit integers are supported on your platform, \
	please set s64 manually.
#endif

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit */
	/*! @brief If your machine support 32 bit
	define the MACHINE_32_BIT*/
#elif defined MACHINE_32_BIT
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed int s32;/**< used for signed 32bit */
	typedef signed long long int s64;/**< used for signed 64bit */

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit
	- int and long int is same for u32*/
	typedef unsigned long long int u64;/**< used for unsigned 64bit */

	/* If your machine support 64 bit
	define the MACHINE_64_BIT*/
#elif defined MACHINE_64_BIT
	/*signed integer types*/
	typedef signed char  s8;/**< used for signed 8bit */
	typedef signed short int s16;/**< used for signed 16bit */
	typedef signed int s32;/**< used for signed 32bit */
	typedef signed long int s64;/**< used for signed 64bit */

	/*unsigned integer types*/
	typedef unsigned char u8;/**< used for unsigned 8bit */
	typedef unsigned short int u16;/**< used for unsigned 16bit */
	typedef unsigned int u32;/**< used for unsigned 32bit */
	typedef unsigned long int u64;/**< used for unsigned 64bit */

#else
#warning The data types defined above which not supported \
	define the data types manually
#endif
#endif
#endif

/* sensor_api_common_types.h */

/***************************************************************************
	Module globals, typedefs
****************************************************************************/

/***************************************************************************
	Function definition
****************************************************************************/

#endif


