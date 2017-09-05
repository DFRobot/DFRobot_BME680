#include "DFRobot_BME680.h"

const uint8_t bme_addr = 0x76;  //bme I2C address

DFRobot_BME680 bme(bme_addr);


void setup(void) 
{
	delay(2000);
	Serial.begin(115200);
	while(!Serial);  //wait serial
	if(bme.init()) {  //Return true if initialization succeeds, false otherwise
		Serial.println("init sucessful");
	} else {
		Serial.println("init faild");
		for(;;);
	}
	Serial.println();
}


void loop(void) 
{
	float     temp = 0, pressure = 0, humidity = 0, altitude = 0;
	uint16_t  gas = 0;
	uint8_t   status = 0;

	delay(1000);
	bme.startConvert();             //to get a accurate values
	temp = bme.readTempture();      //float tempture, unit degree Celsius, this is account to two decimal places
	pressure = bme.readPressure();  //float pressure, Unit Unit MPa, this is account to two decimal places
	altitude = bme.readAltitude();  //float altitude, Unit metre, this is account to one decimal places
	humidity = bme.readHumidity();  //float humidity, Unit relative humidity, this is account to two decimal places
	gas = bme.readGas();            //uint16_t gas, Unit ppm, this is account to one decimal places
	Serial.println();
	Serial.print("tempture : ");
	Serial.print(temp, 2);
	Serial.println(" C");	
	Serial.print("pressure : ");
	Serial.print(pressure, 2);
	Serial.println(" pa");	
	Serial.print("humidity : ");
	Serial.print(humidity, 2);
	Serial.println(" %rh");	
	Serial.print("gas : ");
	Serial.print(gas);
	Serial.println(" ppm");
}

