/*!
 * @file IAQ_I2C.ino
 * @brief connect bme680 I2C interface with your board (please reference board compatibility)
 * @n Temprature, Humidity, pressure, altitude, calibrated altitude, gas resistance and IAQ data will be printed via serial.
 * @note This demo only support ESP8266 MCU
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [Frank](jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-7
 * @url https://github.com/DFRobot/DFRobot_BME680
 */
 
#include "DFRobot_BME680_I2C.h"
#include "Wire.h"

/*use an accurate altitude to calibrate sea level air pressure*/
#define CALIBRATE_PRESSURE

DFRobot_BME680_I2C bme(0x77);  //0x77 I2C address


float seaLevel; 
void setup()
{
  uint8_t       rslt = 1;
  Serial.begin(115200);
  while(!Serial);
  delay(1000);
  Serial.println();
  while(rslt != 0) {
    rslt = bme.begin();
    if(rslt != 0) {
      Serial.println("bme begin failure");
      delay(2000);
    }
  }
  Serial.println("bme begin successful");
  bme.supportIAQ();
}

void loop()
{
  static uint8_t       calibrated = 0;
  
  #ifdef CALIBRATE_PRESSURE
  if(calibrated == 0) {
    if(bme.iaqUpdate() == 0) {
      /*You can use an accurate altitude to calibrate sea level air pressure. 
       *And then use this calibrated sea level pressure as a reference to obtain the calibrated altitude.
       *In this case,525.0m is chendu accurate altitude.
       */
      seaLevel = bme.readSeaLevel(525.0);
      Serial.print("seaLevel :");
      Serial.println(seaLevel);
      calibrated = 1;
    }
  }
  #else
    calibrated = 1;
  #endif
  
  if(calibrated) {
    uint8_t rslt = bme.iaqUpdate();
    if(rslt == 0) {
      Serial.println();
      Serial.print("timestamp(ms) :");
      Serial.println(millis());
      Serial.print("temperature(C) :");
      Serial.println(bme.readTemperature(), 2);
      Serial.print("pressure(Pa) :");
      Serial.println(bme.readPressure());
      Serial.print("humidity(%rh) :");
      Serial.println(bme.readHumidity(), 2);
      Serial.print("altitude(m) :");
      Serial.println(bme.readAltitude());
#ifdef CALIBRATE_PRESSURE
      Serial.print("calibrated altitude(m) :");
      Serial.println(bme.readCalibratedAltitude(seaLevel));
#endif
      Serial.print("gas resistance :");
      Serial.println(bme.readGasResistance());
      if(bme.isIAQReady()) {
        Serial.print("IAQ :");
        float iaq = bme.readIAQ();
        Serial.print(iaq);
        if(iaq < 50) Serial.println(" good");
        else if(iaq < 100) Serial.println(" average");
        else if(iaq < 150) Serial.println(" little bad");
        else if(iaq < 200) Serial.println(" bad");
        else if(iaq < 300) Serial.println(" worse");
        else Serial.println(" very bad");
      } else {
        Serial.print("IAQ not ready, please wait about ");
        Serial.print((int)(305000-millis())/1000);
        Serial.println(" seconds");
      }
    }
  }
}


