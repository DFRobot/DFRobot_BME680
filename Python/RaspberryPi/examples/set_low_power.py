'''
file set_low_power.py

connect bme680 I2C interface with your board (please reference board compatibility)
You can set sensor low power mode or wake up mode.

Copyright   [DFRobot](http://www.dfrobot.com), 2016
Copyright   GNU Lesser General Public License

version  V1.0
date  2019-7-2
'''
import sys
sys.path.append('../')
from DFRobot_BME680 import DFRobot_BME680
import time

sensor = DFRobot_BME680()

#sensor.set_power_mode(sensor.SLEEP_MODE) # set low power mode
sensor.set_power_mode(sensor.FORCED_MODE) # set wake up mode
sensor.get_power_mode() # get current power mode

if sensor.get_power_mode() == 141:
    print("Current power mode is forced")
else:
    print("Current power mode is sleep")

while True:
    time.sleep(1)
