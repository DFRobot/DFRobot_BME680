/**\mainpage
 * Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of the
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 * The information provided is believed to be accurate and reliable.
 * The copyright holder assumes no responsibility
 * for the consequences of use
 * of such information nor for any infringement of patents or
 * other rights of third parties which may result from its use.
 * No license is granted by implication or otherwise under any patent or
 * patent rights of the copyright holder.
 *
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

    uint8_t       bme680_I2CAddr = 0;

    int16_t       begin(void);
    void          update(void);
    int8_t        iaqUpdate(void);
    void          startConvert(void);
    float         readTemperature(void);
    float         readPressure(void);
    float         readHumidity(void);
    float         readAltitude(void);
    float         readCalibratedAltitude(float seaLevel);
    float         readGasResistance(void);
    float         readSeaLevel(float altitude);
    float         readIAQ(void);
    
    void          setParam(eBME680_param_t eParam, uint8_t dat);
    void          setGasHeater(uint16_t temp, uint16_t t);
    uint8_t       isIAQReady(void);
  
  private:
    void          writeParamHelper(uint8_t reg, uint8_t dat, uint8_t addr);
};

#endif


