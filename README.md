# BME680
BME680 is an integrated environmental sensor developed specifically for mobile applications and wearables where size and low power consumption are key requirements. Expanding Bosch Sensortec’s existing family of environmental sensors, the BME680 integrates for the first time individual high linearity and high accuracy sensors for gas, pressure, humidity and temperature.

![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/SEN0248/SEN0248svg1.png)

## DFRobot_EINKBWR_IL0376F Library for Arduino
---------------------------------------------------------
Provides an Arduino library for reading and interpreting Bosch BME680 data over I2C over SPI.

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)

* [History](#history)
* [Credits](#credits)
* [Compatibility](#compatibility)
<snippet>
<content>

## Summary

Reads temperature, humidity, gas, pressure and calculates altitude.

## Installation

To use this library download the zip file, uncompress it to a folder named DFRobot_BME680. 
Download the zip file first to use this library and uncompress it to a folder named DFRobot_BME680. 

## Methods

```C++

#include <DFRobot_BME680_SPI.h>  //
#include <DFRobot_BME680_I2C.h>  //choose at least one

DFRobot_BME680_I2C bme(I2C_address);
DFRobot_BME680_SPI bme(pin_cs);


/*
 * @brief begin BME680 device
 *
 * @return result
 *    ture : falid
 *    false : succussful
 */
boolean begin(void);

/*
 * @brief start convert to get a accurate values
 */
void startConvert(void);

/*
 * @brief update all data to MCU ram
 */
void update(void);

/*
 * @brief read the temperature value (unit ℃)
 *
 * @return temperature value, this value has two decimal points
 */
float readTempture(void);

/*
 * @brief read the humidity value (unit %rh)
 *
 * @return humidity value, this value has two decimal points
 */
float readHumidity(void);

/*
 * @brief read the pressure value (unit pa)
 *
 * @return pressure value, this value has two decimal points
 */
float readPressure(void);

/*
 * @brief read the altitude (unit meter)
 *
 * @return altitude value, this value has two decimal points
 */
float readAltitude(void);

/*
 * @brief read the gas resistance(unit ohm)
 *
 * @return temperature value, this value has two decimal points
 */
float readGasResistance(void);

```

## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |       √      |             |            | 
Arduino uno |       √      |             |            | 
Arduino leonardo |      √       |             |            | 

## History

- Sep 4, 2017 - Version 1.0.0 released.
- Sep 28, 2017 - Version 1.1.0 released.
- Oct 11, 2017 - Version 2.0.0 released.
- Oct 19, 2017 - Version 2.1.0 released.

## Credits

Written by DFRobot_xiaowo, 2017. (Welcome to our [website](https://www.dfrobot.com/))
