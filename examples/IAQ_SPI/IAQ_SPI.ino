#include "DFRobot_BME680_SPI.h"
#include "SPI.h"

/*use an accurate altitude to calibrate sea level air pressure*/
#define CALIBRATE_PRESSURE

DFRobot_BME680_SPI bme(D3);

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
      Serial.println("bme begin faild");
      delay(2000);
    }
  }
  Serial.println("bme begin successful");
  bme.supportIAQ();
}

void loop()
{
  static uint8_t       firstCalivrate = 0;
  #ifdef CALIBRATE_PRESSURE
  if(firstCalivrate == 0) {
    if(bme.iaqUpdate() == 0) {
      /*You can use an accurate altitude to calibrate sea level air pressure. 
       *And then use this calibrated sea level pressure as a reference to obtain the calibrated altitude.
       *In this case,525.0m is chendu accurate altitude.
       */
      seaLevel = bme.readSeaLevel(525.0);
      Serial.print("seaLevel :");
      Serial.println(seaLevel);
      firstCalivrate = 1;
    }
  }
  #else
    firstCalivrate = 1;
  #endif
  if(firstCalivrate) {
    uint8_t rslt = bme.iaqUpdate();
    if(rslt == 0) {
      Serial.println();
      Serial.print("time(ms) :");
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
      Serial.println(bme.reaCalibratedAltitude(seaLevel));
#endif
      Serial.print("gas resistance :");
      Serial.println(bme.readGasResistance());
      Serial.print("IAQ :");
      float iaq = bme.readIAQ();
      Serial.print(iaq);
      if(iaq < 50) Serial.println(" good");
      else if(iaq < 100) Serial.println(" average");
      else if(iaq < 150) Serial.println(" little bad");
      else if(iaq < 200) Serial.println(" bad");
      else if(iaq < 300) Serial.println(" worse");
      else Serial.println(" very bad");
    }
  }
}


