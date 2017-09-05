# BME680
Provides an Arduino library for reading and interpreting Bosch BME680 data over I2C.

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

To use this library download the zip file, uncompress it to a folder named BME680. Move the folder to {Arduino Path}/libraries.

## Methods

```C++

#include <DFRobot_BME680.h>

DFRobot_BME680 bme(I2C_address);

// bme init.
// Return boolean = init result. if successful, return 1, else return 0
boolean init(void);

//start convert to get a accurate values
void startConvert(void);

//Return float = temperature. Unit degree Celsius, this is account to two decimal places
float readTempture(void);

//Return float = humidity. Unit relative humidity, this is account to two decimal places
float readHumidity(void);
	
//Return float = pressure. Unit MPa, this is account to two decimal places
float readPressure(void);

//Return float = gas. Unit Ohm, this is account to one decimal places
float readGas(void);
	
```
	
## History

- Sep 4, 2017 - Version 1.0.0 released.

## Credits

Written by DFRobot_xiaowo, 2017. (Welcome to our [websit](https://www.dfrobot.com/))
