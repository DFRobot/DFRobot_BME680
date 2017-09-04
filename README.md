# BME680
Provides an Arduino library for reading and interpreting Bosch BME680 data over I2C.

## Table of Contents

* [BME680](#bme680)
* [Table of Contents](#table_of_contents)
* [Summary](#summary)
* [Installation](#installation)
* [Methods](#methods)

* [Contributing](#contributing)
* [History](#history)
* [Credits](#credits)
<snippet>
<content>

## Summary

Reads temperature, humidity, gas and pressure. Calculates altitude and dew point.

## Installation

To use this library download the zip file, uncompress it to a folder named BME680. Move the folder to {Arduino Path}/libraries.

## Methods


class BME680() {};

BME680 bme(I2C_address);


#### boolean BME680::init(void)

	bme init.
	Return boolean = init result. if successful, return 1, else return 0

	
#### void BME680::startConvert(void)
	
	start convert to get a accurate values


#### float BME680::readTempture(void)
	
	Return float = temperature. Unit degree Celsius, this is account to two decimal places


#### float BME680::readHumidity(void)
	
	Return float = humidity. Unit relative humidity, this is account to two decimal places
	

#### float BME680::readPressure(void)

	Return float = pressure. Unit MPa, this is account to two decimal places
	
	
#### float BME680::readGas(void)

	Return float = gas. Unit Ohm, this is account to one decimal places
	

## History

- Sep 4, 2017 - Version 1.0.0 released.

## Credits

Written by DFRobot_xiaowo, 2017. (@1003425554@qq.com)
