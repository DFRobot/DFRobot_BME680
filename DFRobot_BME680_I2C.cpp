#include "DFRobot_BME680_I2C.h"


static int8_t bme680_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  Wire.begin();
  Wire.beginTransmission(dev_id);
  Wire.write(reg_addr);
  Wire.endTransmission();
  Wire.requestFrom(dev_id, len);
  while(Wire.available()) {
    *data = Wire.read();
    data ++;
  }
  return 0;
}


static int8_t bme680_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  Wire.begin();
  Wire.beginTransmission(dev_id);
  Wire.write(reg_addr);
  while(len --) {
    Wire.write(*data);
    data ++;
  }
  Wire.endTransmission();
  return 0;
}


static void bme680_delay_ms(uint32_t period)
{
  delay(period);
}


DFRobot_BME680_I2C::DFRobot_BME680_I2C(uint8_t I2CAddr) :
                    DFRobot_BME680(bme680_i2c_read, bme680_i2c_write, bme680_delay_ms, eBME680_INTERFACE_I2C)
{
  DFRobot_BME680::bme680_I2CAddr = I2CAddr;
}


