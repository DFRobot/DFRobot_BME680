'''
file read_all_data.py

connect bme680 I2C interface with your board (please reference board compatibility)
Temprature, Humidity, pressure, altitude, calibrate altitude and gas resistance data will print on serial window.

Copyright   [DFRobot](http://www.dfrobot.com), 2016
Copyright   GNU Lesser General Public License

version  V1.0
date  2019-7-2
'''

from DFRobot_BME680 import BME680
import time

sensor = BME680()

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

sensor.set_humidity_oversample(sensor.OS_2X)
sensor.set_pressure_oversample(sensor.OS_4X)
sensor.set_temperature_oversample(sensor.OS_8X)
sensor.set_filter(sensor.FILTER_SIZE_3)
sensor.set_gas_status(sensor.ENABLE_GAS_MEAS)
'''
print("\n\nInitial reading:")
for name in dir(sensor.data):
    value = getattr(sensor.data, name)

    if not name.startswith('_'):
        print("{}: {}".format(name, value))
'''
sensor.set_gas_heater_temperature(320)
sensor.set_gas_heater_duration(150)
sensor.select_gas_heater_profile(0)


print("\n\nPolling:")
while True:
    if sensor.get_sensor_data():
        print("temperature: {0:.2f} C, pressure: {1:.2f} hPa, humidity: {2:.2f} %RH".format(sensor.data.temperature, sensor.data.pressure, sensor.data.humidity))

    time.sleep(1)
