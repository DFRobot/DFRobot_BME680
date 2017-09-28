#include "DFRobot_BME680_SPI.h"


DFRobot_BME680_SPI::DFRobot_BME680_SPI(uint8_t pin_cs)
{
  this->pin_cs = pin_cs;
  pinMode(this->pin_cs, OUTPUT);
  digitalWrite(this->pin_cs, 1);
}


void DFRobot_BME680_SPI::readReg(uint8_t addr, uint8_t count, uint8_t* pBuf)
{
  uint8_t i = 0;
  SPI.begin();
  digitalWrite(this->pin_cs, 0);
  SPI.transfer(addr | 0x80);
  for(; i < count; i ++) {
    *pBuf = SPI.transfer(0x00);
    pBuf ++;
  }
  digitalWrite(this->pin_cs, 1);
}


void DFRobot_BME680_SPI::writeReg(uint8_t addr, uint8_t dat)
{
  SPI.begin();
  digitalWrite(this->pin_cs, 0);
  SPI.transfer(addr);
  SPI.transfer(dat);
  digitalWrite(this->pin_cs, 1);
}


uint8_t DFRobot_BME680_SPI::readID(void)
{
  uint8_t       id = 0;
  uint8_t       var1 = 0;
  this->writeReg(BME680_STATUS, 0x00);
  this->writeReg(BME680_RESET, 0xb6);
	delay(100);
	this->readReg(BME680_ID, 1, &id);
  Serial.print("ID is :0x");
  Serial.println(id, HEX);
  return id;
}

