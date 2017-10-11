#include "DFRobot_BME680_SPI.h"
#include "SPI.h"

#ifdef __AVR__
const uint8_t bme_cs = 3;
#elif defined ESP_PLATFORM
const uint8_t bme_cs = D3;
#elif defined __ets__
const uint8_t bme_cs = D3;
#else
  #error unknow board
#endif

DFRobot_BME680_SPI bme(bme_cs);


void setup()
{
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Serial.println();
  Serial.print(bme.begin());
}

void loop()
{
  bme.startConvert();
  delay(1000);
  bme.update();
  Serial.println();
  Serial.print("temperature(C) :");
  Serial.println(bme.readTempture(), 2);
  Serial.print("pressure(Pa) :");
  Serial.println(bme.readPressure());
  Serial.print("humidity(%rh) :");
  Serial.println(bme.readHumidity(), 2);
  Serial.print("gas(ppm) :");
  Serial.println(bme.readGas());
  Serial.print("gas resistance(ohm) :");
  Serial.println(bme.readGasResistance());
  Serial.print("altitude(m) :");
  Serial.println(bme.readAltitude());
}