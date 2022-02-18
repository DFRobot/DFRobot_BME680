/**
 * @file DFRobot_BME680_SPI.cpp
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */
#include "DFRobot_BME680_SPI.h"

static uint8_t bme680_cs = 0;


static int8_t bme680_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(bme680_cs, 0);
  SPI.transfer(reg_addr | 0x80);
  while(len --) {
    *data = SPI.transfer(0x00);
    data ++;
  }
  digitalWrite(bme680_cs, 1);
  SPI.endTransaction();
  return 0;
}


static int8_t bme680_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  SPI.begin();
  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(bme680_cs, 0);
  SPI.transfer(reg_addr);
  while(len --) {
    SPI.transfer(*data);
    data ++;
  }
  digitalWrite(bme680_cs, 1);
  SPI.endTransaction();
  return 0;
}


DFRobot_BME680_SPI::DFRobot_BME680_SPI(uint8_t pin_cs) :
                    DFRobot_BME680(bme680_spi_read, bme680_spi_write, bme680_delay_ms, eBME680_INTERFACE_SPI)
{
  bme680_cs = pin_cs;
  pinMode(bme680_cs, OUTPUT);
  digitalWrite(bme680_cs, 1);
}


void DFRobot_BME680_SPI::setConvertAndUpdate()
{
  bsec_iot_init(0.33333f, 0, bme680_spi_write, bme680_spi_read, bme680_delay_ms, 0x77, BME680_SPI_INTF);
}

