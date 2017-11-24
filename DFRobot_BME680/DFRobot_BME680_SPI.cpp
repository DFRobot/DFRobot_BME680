#include "DFRobot_BME680_SPI.h"

static uint8_t bme680_cs = 0;


static int8_t bme680_spi_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  SPI.begin();
  digitalWrite(bme680_cs, 0);
  SPI.transfer(reg_addr);
  while(len --) {
    *data = SPI.transfer(0x00);
    data ++;
  }
  digitalWrite(bme680_cs, 1);
  return 0;
}


static int8_t bme680_spi_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
  SPI.begin();
  digitalWrite(bme680_cs, 0);
  SPI.transfer(reg_addr);
  while(len --) {
    SPI.transfer(*data);
    data ++;
  }
  digitalWrite(bme680_cs, 1);
  return 0;
}


static void bme680_delay_ms(uint32_t period)
{
  delay(period);
}


DFRobot_BME680_SPI::DFRobot_BME680_SPI(uint8_t pin_cs) :
                    DFRobot_BME680(bme680_spi_read, bme680_spi_write, bme680_delay_ms, eBME680_INTERFACE_SPI)
{
  bme680_cs = pin_cs;
  pinMode(bme680_cs, OUTPUT);
  digitalWrite(bme680_cs, 1);
}


