/**
 * @file DFRobot_BME680.cpp
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */
#include "DFRobot_BME680.h"

static struct        bme680_dev bme680_sensor;
static struct        bme680_field_data bme680_data;
static uint8_t       convertCmd = (0x05 << 5) | (0x05 << 2) | (0x01);
static uint8_t       iaqReady_ = 0;

void bme680_outputReady(int64_t timestamp, float iaq, uint8_t iaq_accuracy, float temperature,
                        float humidity, float pressure, float raw_temperature, float raw_humidity,
                        float gas, bsec_library_return_t bsec_status)
{
  if(iaq_accuracy != 0) bme680_data.gas_index = iaq;
  bme680_data.temperature = temperature;
  bme680_data.humidity = humidity;
  bme680_data.pressure = pressure;
  if(iaq_accuracy != 0) iaqReady_ = 1;
}


void bme680_delay_ms(uint32_t period)
{
  delay(period);
}


int64_t bme680_getus(void)
{
  return (millis() * 1000);
}


DFRobot_BME680::DFRobot_BME680(bme680_com_fptr_t readReg, bme680_com_fptr_t writeReg, 
                               bme680_delay_fptr_t delayMS, eBME680_INTERFACE interface)
{
  bme680_sensor.read = readReg;
  bme680_sensor.write = writeReg;
  bme680_sensor.delay_ms = delayMS;
  switch(interface) {
    case eBME680_INTERFACE_I2C: bme680_sensor.intf = BME680_I2C_INTF; break;
    case eBME680_INTERFACE_SPI: bme680_sensor.intf = BME680_SPI_INTF; break;
  }
}


int16_t DFRobot_BME680::begin(void)
{
  bme680_sensor.dev_id = this->bme680_I2CAddr;
  if(bme680_init(&bme680_sensor) != BME680_OK) {
    return -1;
  }
  uint8_t       set_required_settings;
  int8_t        rslt = 0;

	/* Set the temperature, pressure and humidity settings */
	//bme680_sensor.tph_sett.os_hum = BME680_OS_2X;
	//bme680_sensor.tph_sett.os_pres = BME680_OS_4X;
	//bme680_sensor.tph_sett.os_temp = BME680_OS_8X;
	//bme680_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

  
  bme680_sensor.tph_sett.os_hum = 5;
  bme680_sensor.tph_sett.os_pres = 5;
  bme680_sensor.tph_sett.os_temp = 5;
  bme680_sensor.tph_sett.filter = 4;

  /* Set the remaining gas sensor settings and link the heating profile */
  bme680_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;
  /* Create a ramp heat waveform in 3 steps */
  bme680_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
  bme680_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

  /* Select the power mode */
  /* Must be set before writing the sensor configuration */
  bme680_sensor.power_mode = BME680_FORCED_MODE; 

  /* Set the required sensor settings needed */
  set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL 
   | BME680_GAS_SENSOR_SEL;

  /* Set the desired sensor configuration */
  rslt = bme680_set_sensor_settings(set_required_settings, &bme680_sensor);

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(&bme680_sensor);

	/* Get the total measurement duration so as to sleep or wait till the
	 * measurement is complete */
	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, &bme680_sensor);
	bme680_sensor.delay_ms(meas_period); /* Delay till the measurement is ready */
  return 0;
}


void DFRobot_BME680::startConvert(void)
{
  bme680_sensor.write(bme680_sensor.dev_id, 0x74, &convertCmd, 1);
}


void DFRobot_BME680::update(void)
{
  bme680_get_sensor_data(&bme680_data, &bme680_sensor);
}


int8_t DFRobot_BME680::iaqUpdate(void)
{
  uint8_t       gasBuf[2] = {0};
  uint16_t      gasADC = 0;
  uint8_t       gasRange = 0;
  if(bsec_iot_loop(bme680_delay_ms, bme680_getus, bme680_outputReady) == 0) {
    bme680_get_regs(0x2a, gasBuf, 2, &bme680_sensor);
    gasADC = (uint16_t) ((uint32_t) gasBuf[0] * 4 | (((uint32_t) gasBuf[1]) / 64));
    gasRange = gasBuf[1] & BME680_GAS_RANGE_MSK;
    bme680_data.gas_resistance = calc_gas_resistance(gasADC, gasRange, &bme680_sensor);
    return 0;
  }
  return 1;
}


float DFRobot_BME680::readTemperature(void)
{
  return bme680_data.temperature;
}


float DFRobot_BME680::readPressure(void)
{
  return bme680_data.pressure;
}


float DFRobot_BME680::readHumidity(void)
{
  return bme680_data.humidity;
}


float DFRobot_BME680::readAltitude(void)
{
  return (1.0 - pow((float)bme680_data.pressure / 100.0f / BME680_SEALEVEL, 0.190284)) * 287.15 / 0.0065;
}


float DFRobot_BME680::readCalibratedAltitude(float seaLevel)
{
    //data->altitude = 44330.0 * (1.0 - pow((float) data->pressure / 100.0f / BME680_SEALEVEL, 0.1903));
   return (1.0 - pow((float) bme680_data.pressure / seaLevel, 0.190284)) * 287.15 / 0.0065;
}


float DFRobot_BME680::readGasResistance(void)
{
  return bme680_data.gas_resistance;
}


float DFRobot_BME680::readSeaLevel(float altitude)
{
  return (bme680_data.pressure / pow(1.0 - (altitude / 44330.0), 5.255));
}


float DFRobot_BME680::readIAQ(void)
{
  return bme680_data.gas_index;
}


void DFRobot_BME680::setParam(eBME680_param_t eParam, uint8_t dat)
{
  if(dat > 0x05) return;
  switch(eParam) {
    case eBME680_PARAM_TEMPSAMP: writeParamHelper(0x74, dat, 0x07 << 5); break;
    case eBME680_PARAM_PREESAMP: writeParamHelper(0x74, dat, 0x07 << 2); break;
    case eBME680_PARAM_HUMISAMP: writeParamHelper(0x72, dat, 0x07); break;
    case eBME680_PARAM_IIRSIZE: writeParamHelper(0x75, dat, 0x07 << 2); break;
  }
}


void DFRobot_BME680::setGasHeater(uint16_t temp, uint16_t t)
{
  bme680_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
  bme680_sensor.gas_sett.heatr_dur = 150; /* milliseconds */
  uint8_t set_required_settings = BME680_GAS_SENSOR_SEL;
  bme680_set_sensor_settings(set_required_settings, &bme680_sensor);
}


uint8_t DFRobot_BME680::isIAQReady(void)
{
  return iaqReady_;
}


void DFRobot_BME680::writeParamHelper(uint8_t reg, uint8_t dat, uint8_t addr)
{
  uint8_t       var1 = 0;
  uint8_t       addrCount = 0;
  if(bme680_sensor.intf == BME680_SPI_INTF) bme680_sensor.write(bme680_sensor.dev_id, 0x73, 0x00, 1);
  bme680_sensor.read(bme680_sensor.dev_id, reg, &var1, 1);
  var1 &= ~addr;
  while(!(addr & 0x01)) {
    addrCount ++;
    addr >>= 1;
  }
  var1 |= dat << addrCount;
  bme680_sensor.write(bme680_sensor.dev_id, reg, &var1, 1);
}

