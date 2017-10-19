#include "DFRobot_BME680_I2C.h"
#include "Wire.h"

#ifdef __AVR__
#elif defined ESP_PLATFORM
#elif defined __ets__
#else
  #error unknow board
#endif

DFRobot_BME680_I2C bme(0x77);  //0x77 I2C address


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
  Serial.println(bme.readTemperature(), 2);
  Serial.print("pressure(Pa) :");
  Serial.println(bme.readPressure());
  Serial.print("humidity(%rh) :");
  Serial.println(bme.readHumidity(), 2);
  Serial.print("gas resistance(ohm) :");
  Serial.println(bme.readGasResistance());
  Serial.print("altitude(m) :");
  Serial.println(bme.readAltitude());
}
