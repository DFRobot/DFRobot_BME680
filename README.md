# BME680
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
 * @brief begin BME680 device and return result(1: successful, 0: faild)
 */
boolean begin(void);

/*
 * @brief start convert to get a accurate values
 */
void startConvert(void);

/*
 * @brief read the temperature value (unit ℃)
 */
float readTempture(void);

/*
 * @brief read the humidity value (unit %rh)
 */
float readHumidity(void);

/*
 * @brief read the pressure value (unit pa)
 */
float readPressure(void);

/*
 * @brief read the gas altitude (unit meter)
 */
float readAltitude(void);

/*
 * @brief read the gas resistance(unit ohm)
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
- OCT 19, 2017 - Version 2.1.0 released.

## Credits

Written by DFRobot_xiaowo, 2017. (Welcome to our [website](https://www.dfrobot.com/))
