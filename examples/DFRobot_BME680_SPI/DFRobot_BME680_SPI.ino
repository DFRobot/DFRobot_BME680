/*
 * file DFRobot_BME680_I2C.ino
 *
 * @ https://github.com/DFRobot/DFRobot_BME680
 *
 * Connect bme680 4 wires SPI interface with your board (please reference board compatibility).
 * BME680 cs pin connect to D3 on esp8266 and esp32 board, on AVR board is IO 3.
 *
 * Temprature, Humidity, pressure, altitude, calibrate altitude and gas resistance data will print on serial window.
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2017-12-7
 */

#include "DFRobot_BME680_SPI.h"
#include "SPI.h"

#ifdef __AVR__
const uint8_t bme_cs = 3;
#elif ((defined ESP_PLATFORM) || (defined __ets__))
const uint8_t bme_cs = D3;
#else
  #error unknow board
#endif

/*use an accurate altitude to calibrate sea level air pressure*/
#define CALIBRATE_PRESSURE

DFRobot_BME680_SPI bme(bme_cs);

float seaLevel; 
void setup()
{
  uint8_t rslt = 1;
  Serial.begin(9600);
  while(!Serial);
  delay(1000);
  Serial.println();
  while(rslt != 0) {
    rslt = bme.begin();
    if(rslt != 0) {
      Serial.println("bme begin faild");
      delay(2000);
    }
  }
  Serial.println("bme begin successful");
  #ifdef CALIBRATE_PRESSURE
  bme.startConvert();
  delay(1000);
  bme.update();
  /*You can use an accurate altitude to calibrate sea level air pressure. 
   *And then use this calibrated sea level pressure as a reference to obtain the calibrated altitude.
   *In this case,525.0m is chendu accurate altitude.
   */
  seaLevel = bme.readSeaLevel(525.0);
  Serial.print("seaLevel :");
  Serial.println(seaLevel);
  #endif
}

void loop()
{
  bme.startConvert();
  delay(1000);
  bme.update();
  Serial.println();
  Serial.print("temperature(C) :");
  Serial.println(bme.readTemperature() / 100, 2);
  Serial.print("pressure(Pa) :");
  Serial.println(bme.readPressure());
  Serial.print("humidity(%rh) :");
  Serial.println(bme.readHumidity() / 1000, 2);
  Serial.print("gas resistance(ohm) :");
  Serial.println(bme.readGasResistance());
  Serial.print("altitude(m) :");
  Serial.println(bme.readAltitude());
  #ifdef CALIBRATE_PRESSURE
  Serial.print("calibrated altitude(m) :");
  Serial.println(bme.readCalibratedAltitude(seaLevel));
  #endif
}
