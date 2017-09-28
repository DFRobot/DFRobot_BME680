#include "DFRobot_BME680_SPI.h"
#include "DFRobot_BME680_I2C.h"

const uint8_t bme_addr = 0x77;  //bme I2C method address
const uint8_t bme_cs = D3;  //bme SPI method cs pin

//DFRobot_BME680_SPI bme(bme_cs);  //SPI method
DFRobot_BME680_I2C bme(bme_addr);  //I2C method


void setup(void)
{
	delay(500);
	Serial.begin(115200);
	while(!Serial);  //wait serial
  Serial.println("BME680 TEST");
	if(bme.begin()) {
		Serial.println("init sucessful");
	} else {
		Serial.println("init faild");
		for(;;);
	}
	Serial.println();
}


void loop(void)
{
	float     temp = 0, pressure = 0, humidity = 0, altitude = 0, gasResistance = 0;
	uint16_t  gas = 0;
	uint8_t   status = 0;

  delay(1000);
	bme.startConvert();             //to get a accurate values
  delay(1);
	temp = bme.readTempture();      //float tempture, unit degree Celsius, this is account to two decimal places
	pressure = bme.readPressure();  //float pressure, Unit Unit MPa, this is account to two decimal places
	altitude = bme.readAltitude();  //float altitude, Unit metre, this is account to one decimal places
	humidity = bme.readHumidity();  //float humidity, Unit relative humidity, this is account to two decimal places
	gas = bme.readGas();            //uint16_t gas, Unit ppm, this is account to one decimal places
  gasResistance = bme.readGasResistance();  //float resistance, Unit ohm, this is account to two decimal places
	Serial.println();
	Serial.print("tempture :");
	Serial.print(temp, 2);
	Serial.println(" C");
	Serial.print("pressure :");
	Serial.print(pressure, 2);
	Serial.println(" pa");
	Serial.print("altitude :");
	Serial.print(altitude, 1);
	Serial.println(" m");
	Serial.print("humidity :");
	Serial.print(humidity, 2);
	Serial.println(" %rh");
	Serial.print("gas :");
	Serial.print(gas);
  Serial.println(" ppm");
  Serial.print("gas resistance :");
  Serial.print(gasResistance);
	Serial.println(" ohm");
}

