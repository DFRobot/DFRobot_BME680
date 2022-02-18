/**
 * @file DFRobot_BME680.h
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef DFROBOT_BME680_H
#define DFROBOT_BME680_H

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

#include "bsec_integration.h"

#define BME680_SEALEVEL 1015

/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void *) 0)
#endif
#endif

enum eBME680_INTERFACE {
  eBME680_INTERFACE_SPI,
  eBME680_INTERFACE_I2C
};

typedef void (*pfStartConvert_t)(void);
typedef void (*pfUpdate_t)(void);

#define supportIAQ()        setConvertAndUpdate();

void bme680_delay_ms(uint32_t period);
int64_t bme680_getus(void);

void bme680_outputReady(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature, float humidity,
                        float pressure, float raw_temperature, float raw_humidity, float gas, bsec_library_return_t bsec_status);

typedef enum {
  eBME680_PARAM_TEMPSAMP,
  eBME680_PARAM_HUMISAMP,
  eBME680_PARAM_PREESAMP,
  eBME680_PARAM_IIRSIZE
} eBME680_param_t;
                        
class DFRobot_BME680
{
public:
  DFRobot_BME680(bme680_com_fptr_t readReg, bme680_com_fptr_t writeReg, bme680_delay_fptr_t delayMS, eBME680_INTERFACE interface);
  uint8_t bme680_I2CAddr = 0;
  /**
   * @fn begin
   * @brief begin BME680 device
   * @return result
   * @retval  non-zero : falid
   * @retval  0        : succussful
   */
  int16_t begin(void);
  /**
   * @fn update
   * @brief update all data to MCU ram
   */
  void    update(void);
  /**
   * @fn iaqUpdate
   * @brief update all data to MCU ram with IAQ (only for esp8266 now)
   *
   * @return result:
   * @retval 0 :complete
   * @retval 1 :busy
   */
  int8_t  iaqUpdate(void);
  /**
   * @fn startConvert
   * @brief start convert to get a accurate values
   */
  void  startConvert(void);
  /**
   * @fn readTemperature
   * @brief read the temperature value (unit C)
   *
   * @return temperature valu, this value has two decimal points
   */
  float readTemperature(void);
  /**
   * @fn readPressure
   * @brief read the pressure value (unit pa)
   *
   * @return pressure value, this value has two decimal points
   */
  float readPressure(void);
  /**
   * @fn readHumidity
   * @brief read the humidity value (unit %rh)
   * @return humidity value, this value has two decimal points
   */
  float readHumidity(void);
  /**
   * @fn readAltitude
   * @brief read the altitude (unit meter)
   * @return altitude value, this value has two decimal points
   */
  float readAltitude(void);
  /**
   * @fn readCalibratedAltitude
   * @brief read the Calibrated altitude (unit meter)
   *
   * @param seaLevel  normalised atmospheric pressure
   *
   * @return calibrated altitude value , this value has two decimal points
   */
  float readCalibratedAltitude(float seaLevel);
  /**
   * @fn readGasResistance
   * @brief read the gas resistance(unit ohm)
   * @return temperature value, this value has two decimal points
   */
  float readGasResistance(void);
  /**
   * @fn readSeaLevel
   * @brief read normalised atmospheric pressure (unit pa)
   * @param altitude   accurate altitude for normalising
   * @return normalised atmospheric pressure
   */
  float readSeaLevel(float altitude);
  /**
   * @fn readIAQ
   * @brief read IAQ
   * @return The result of IAQ
   */
  float readIAQ(void);
  /**
   * @fn setParam
   * @brief set bme680 parament
   *
   * @param eParam        :which param you want to change
   *        dat           :object data, can't more than 5
   */  
  void    setParam(eBME680_param_t eParam, uint8_t dat);
  /**
   * @fn setGasHeater
   * @brief set bme680 gas heater
   * @param temp        :your object temp
   * @param t           :time spend in milliseconds
   */
   void    setGasHeater(uint16_t temp, uint16_t t);
  /**
   * @fn isIAQReady
   * @brief check IAQ ready
   * @return result:
   * @retval 0 :ready
   * @retval 1 :not ready
   */
  uint8_t isIAQReady(void);
  
  private:
    void          writeParamHelper(uint8_t reg, uint8_t dat, uint8_t addr);
};

#endif


