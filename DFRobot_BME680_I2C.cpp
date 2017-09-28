#include "DFRobot_BME680_I2C.h"


DFRobot_BME680_I2C::DFRobot_BME680_I2C(uint8_t addr)
{
  this->I2C_addr = addr;
}


void DFRobot_BME680_I2C::readReg(uint8_t addr, uint8_t count, uint8_t* pBuf)
{
  Wire.begin();
  Wire.beginTransmission(this->I2C_addr);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(this->I2C_addr, count);
	while(Wire.available()) {
		*pBuf = Wire.read();
		pBuf ++;
	}
}


void DFRobot_BME680_I2C::writeReg(uint8_t addr, uint8_t dat)
{
  Wire.begin();
  Wire.beginTransmission(this->I2C_addr);
	Wire.write(addr);
	Wire.write(dat);
	Wire.endTransmission();
}


uint8_t DFRobot_BME680_I2C::readID(void)
{
  uint8_t       id = 0;
  this->writeReg(BME680_RESET, 0xb6);
	delay(100);
	this->readReg(BME680_ID, 1, &id);
  Serial.print("ID is :0x");
  Serial.println(id, HEX);
  return id;
}

