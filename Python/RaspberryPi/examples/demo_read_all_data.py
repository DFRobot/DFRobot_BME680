# -*- coding:utf-8 -*-
from __future__ import print_function


'''!
  @file demo_read_all_data.py
  @brief connect bme680 I2C interface with your board (please reference board compatibility)
  @n Temprature, Humidity, pressure, altitude, calibrate altitude and gas resistance data will print on serial window.
  @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
  @license     The MIT License (MIT)
  @author [luoyufeng](yufeng.luo@dfrobot.com) 
  @version  V1.0
  @date  2019-7-2
  @url https://github.com/DFRobot/DFRobot_BME680
'''


import sys
sys.path.append('../')
from DFRobot_BME680 import DFRobot_BME680
import time

sensor = DFRobot_BME680()

# These calibration data can safely be commented
# out, if desired.
'''
print("Calibration data:")
for name in dir(sensor.calibration_data):

    if not name.startswith('_'):
        value = getattr(sensor.calibration_data, name)

        if isinstance(value, int):
            print("{}: {}".format(name, value))
'''
# These oversampling settings can be tweaked to 
# change the balance between accuracy and noise in
# the data.

sensor.set_humidity_oversample(sensor.OS_2X) #Oversampling value: OS_NONE, OS_1X, OS_2X, OS_4X, OS_8X, OS_16X
sensor.set_pressure_oversample(sensor.OS_4X) #Oversampling value: OS_NONE, OS_1X, OS_2X, OS_4X, OS_8X, OS_16X
sensor.set_temperature_oversample(sensor.OS_8X) #Oversampling value: OS_NONE, OS_1X, OS_2X, OS_4X, OS_8X, OS_16X
sensor.set_filter(sensor.FILTER_SIZE_3) #increasing resolution but reducing bandwidth
sensor.set_gas_status(sensor.ENABLE_GAS_MEAS) #1 for enable and 0 for disable
'''
print("\n\nInitial reading:")
for name in dir(sensor.data):
    value = getattr(sensor.data, name)

    if not name.startswith('_'):
        print("{}: {}".format(name, value))
'''
sensor.set_gas_heater_temperature(320) #value:target temperature in degrees celsius, between 200 ~ 400
sensor.set_gas_heater_duration(150) #value:target duration in milliseconds, between 1 and 4032
sensor.select_gas_heater_profile(0) #value:current gas sensor conversion profile: 0 to 9


print("\n\nPolling:")
while True:
    if sensor.get_sensor_data():
        print("temperature: {0:.2f} C, pressure: {1:.2f} hPa, humidity: {2:.2f} %RH".format(sensor.data.temperature, sensor.data.pressure, sensor.data.humidity))

    time.sleep(1)
