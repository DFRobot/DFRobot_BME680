# BME680 Module
![SVG1](https://raw.githubusercontent.com/DFRobot/binaryfiles/master/TEL0122/TEL0122svg1.png)

# BME680 Library for Arduino
Provides an Arduino library for reading and interpreting Bosch BME680 data over I2C or SPI

## Table of Contents

* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)

* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary

Reads temperature, humidity, gas and pressure. Calculates altitude and dew point.

## Installation

To use this library download the zip file, uncompress it to a folder named DFRbot_BME680Demo. 
Download the zip file first to use this library and uncompress it to a folder named DFRbot_BME680Demo. 

## Methods

```C++

#include <DFRobot_BME680.h>

DFRobot_BME680 bme(I2C_address);

//Performs the initialisation required by the DFRobot_BME680 library.
//Return true if initialization succeeds, false otherwise.
boolean init(void);

//start convert to get a accurate values
void startConvert(void);

//read the temperature value (unit ℃)
float readTempture(void);

//read the humidity value (unit %rh)
float readHumidity(void);
	
//read the pressure value (unit pa)
float readPressure(void);

//read the gas value (unit ppm)
float readGas(void);

//read the gas altitude (unit meter) (need to read pressure first)
float readAltitude(void);
	
```
	
## Compatibility

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |      √       |             |            | 

## History

- Sep 4, 2017 - Version 1.0.0 released.

## Credits

Written by DFRobot_xiaowo, 2017. (Welcome to our [website](https://www.dfrobot.com/))
