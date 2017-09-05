#include "DFRobot_BME680.h"

// Specify BME680 configuration
static uint8_t Posr = P_OSR_16, Hosr = H_OSR_01, Tosr = T_OSR_02, Mode = Forced, IIRFilter = BW0_042ODR, SBy = t_10ms;     // set pressure amd temperature output data rate
// Gas sensor configuration
static uint8_t GWaitMult = gw_1xmult; // choose gas sensor wait time multiplier
static uint8_t numHeatPts = 0x01; // one heat set point
// choose gas wait time in milliseconds x gas wait multiplier 0x00 | 0x59 == 100 ms gas wait time
static uint8_t gasWait[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // must choose at least one non-zero wait time  
static uint8_t resHeat[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // must choose at least one non-zero wait time  

// Data arrays for conversion of raw gas measurements into resistance
static float const_array1[16] = {1, 1, 1, 1, 1, 0.99, 1, 0.992, 1, 1, 0.998, 0.995, 1, 0.99, 1, 1};
static double const_array2[16] = {8000000.0, 4000000.0, 2000000.0, 1000000.0, 499500.4995, 248262.1648, 125000.0, 
63004.03226, 31281.28128, 15625.0, 7812.5, 3906.25, 1953.125, 976.5625, 488.28125, 244.140625};

// t_fine carries fine temperature as global value for BME680
static int32_t t_fine;

static float Temperature, Pressure, Humidity; // stores BME680 pressures sensor pressure and temperature
static uint32_t rawPress, rawTemp;   // pressure and temperature raw count output for BME680
static uint16_t rawHumidity, rawGasResistance;  // variables to hold raw BME680 humidity and gas resistance values

// BME680 compensation parameters
static uint8_t  dig_P10, dig_H6;
static uint16_t dig_T1, dig_P1, dig_H1, dig_H2;
static int16_t  dig_T2, dig_P2, dig_P4, dig_P5, dig_P8, dig_P9, dig_GH2;
static int8_t   dig_T3, dig_P3, dig_P6, dig_P7, dig_H3, dig_H4, dig_H5, dig_H7, dig_GH1, dig_GH3;
static float   temperature_C, temperature_F, pressure, humidity, altitude, resistance; // Scaled output of the BME680
static uint32_t delt_t = 0, count = 0, sumCount = 0, slpcnt = 0;  // used to control display output rate
static uint8_t status0, status1, status2;


DFRobot_BME680::DFRobot_BME680(uint8_t addr)
{	
	this->I2C_addr = addr;
}


boolean DFRobot_BME680::init(void) 
{
	uint8_t id = 0;
	Wire.begin();
	this->writeReg(BME680_RESET, 0xb6);
	delay(100);
	this->readReg(BME680_ID, 1, &id);
	if(id == 0x61) {
		this->writeReg(BME680_CTRL_HUM, 0x07 & Hosr);
		// Set T and P oversampling rates and sensor mode
		this->writeReg(BME680_CTRL_MEAS, Tosr << 5 | Posr << 2 | Mode);
		// Set standby time interval in normal mode and bandwidth
		this->writeReg(BME680_CONFIG, SBy << 5 | IIRFilter << 2);
	 
		// Read and store calibration data
		uint8_t calib[41] = {0};
		this->readReg(BME680_CALIB_ADDR_1, 25, &calib[0]);
		this->readReg(BME680_CALIB_ADDR_2, 16, &calib[25]);
		// temperature compensation parameters
		dig_T1 = (uint16_t)(((uint16_t) calib[34] << 8) | calib[33]);
		dig_T2 = ( int16_t)((( int16_t) calib[2] << 8) | calib[1]);
		dig_T3 = (  int8_t)             (calib[3]);
		// pressure compensation parameters
		dig_P1 = (uint16_t)(((uint16_t) calib[6] << 8) | calib[5]);
		dig_P2 = ( int16_t)((( int16_t) calib[8] << 8) | calib[7]);
		dig_P3 =  ( int8_t)             (calib[9]);
		dig_P4 = ( int16_t)((( int16_t) calib[12] << 8) | calib[11]);
		dig_P5 = ( int16_t)((( int16_t) calib[14] << 8) | calib[13]);
		dig_P6 =  ( int8_t)             (calib[16]);
		dig_P7 =  ( int8_t)             (calib[15]);  
		dig_P8 = ( int16_t)((( int16_t) calib[20] << 8) | calib[19]);
		dig_P9 = ( int16_t)((( int16_t) calib[22] << 8) | calib[21]);
		dig_P10 = (uint8_t)             (calib[23]);
		// humidity compensation parameters
		dig_H1 =  (uint16_t)(((uint16_t) calib[27] << 4) | (calib[26] & 0x0F));
		dig_H2 =  (uint16_t)(((uint16_t) calib[25] << 4) | (calib[26] >> 4));
		dig_H3 =  (int8_t) calib[28];
		dig_H4 =  (int8_t) calib[29];
		dig_H5 =  (int8_t) calib[30];
		dig_H6 = (uint8_t) calib[31];
		dig_H7 =  (int8_t) calib[32];
		// gas sensor compensation parameters
		dig_GH1 =  (int8_t) calib[37];
		dig_GH2 = ( int16_t)((( int16_t) calib[36] << 8) | calib[35]);
		dig_GH3 =  (int8_t) calib[38];
		
		gasWait[0] = GWaitMult | 0x59;  // define gas wait time for heat set point 0x59 == 100 ms
		resHeat[0] = this->TT(200);    // define temperature set point in degrees Celsius for resistance set point 0
		
		this->writeReg(BME680_CTRL_GAS_1, 0x10 | numHeatPts - 1); // write number of heater set points
		// Set gas sampling wait time and target heater resistance
		for(uint8_t ii = 0; ii < numHeatPts; ii++) {
			this->writeReg((BME680_GAS_WAIT_X + ii), gasWait[ii]);
			this->writeReg((BME680_RES_HEAT_X + ii), resHeat[ii]);
		}
		return 1;
	} else {
		return 0;
	}
}


void DFRobot_BME680::readReg(uint8_t addr, uint8_t count, uint8_t *pBuf)
{	
	Wire.beginTransmission(this->I2C_addr);
	Wire.write(addr);
	Wire.endTransmission();
	Wire.requestFrom(this->I2C_addr, count);
	while(Wire.available()) {
		*pBuf = Wire.read();
		pBuf ++;
	}
	Wire.endTransmission();
}


void DFRobot_BME680::writeReg(uint8_t addr, uint8_t dat)
{	
	Wire.beginTransmission(this->I2C_addr);
	Wire.write(addr);
	Wire.write(dat);
	Wire.endTransmission();
}


void DFRobot_BME680::startConvert(void)
{	
	this->writeReg(BME680_CTRL_MEAS, Tosr << 5 | Posr << 2 | Mode);
}


float DFRobot_BME680::readTempture(void)
{	
	uint32_t temp = 0;
	uint8_t rawData[3];  // 20-bit pressure register data stored here
	this->readReg(BME680_FIELD_0_TEMP_MSB, 3, &rawData[0]);
	temp = (uint32_t) (((uint32_t) rawData[0] << 16 | (uint32_t) rawData[1] << 8 | rawData[2]) >> 4);

	int32_t var1 = 0, var2 = 0, var3 = 0, T = 0;
	var1 = ((int32_t) temp >> 3) - ((int32_t)dig_T1 << 1); 
	var2 = (var1 * (int32_t)dig_T2) >> 11;
	var3 = ((((var1 >> 1) * (var1 >> 1)) >> 12) * ((int32_t) dig_T3 << 4)) >> 14;
	t_fine = var2 + var3;
	T = (t_fine * 5 + 128) >> 8;
	return (T / 100.);
}


float DFRobot_BME680::readHumidity(void) {
	
	uint32_t humidity = 0;
	uint8_t rawData[3];  // 20-bit pressure register data stored here
	this->readReg(BME680_FIELD_0_HUM_MSB, 2, &rawData[0]);  
	humidity = (uint16_t) (((uint16_t) rawData[0] << 8 | rawData[1]) );

	int32_t var1 = 0, var2 = 0, var3 = 0, var4 = 0, var5 = 0, var6 = 0, H = 0, T = 0;
	T = (((int32_t) t_fine * 5) + 128) >> 8;
	var1 = (int32_t) humidity  - ((int32_t) ((int32_t)dig_H1 << 4)) - (((T * (int32_t) dig_H3) / ((int32_t)100)) >> 1);
	var2 = ((int32_t)dig_H2 * (((T * (int32_t)dig_H4) / 
				 ((int32_t)100)) + (((T * ((T * (int32_t)dig_H5) / 
				 ((int32_t)100))) >> 6) / ((int32_t)100)) + (int32_t)(1 << 14))) >> 10;
	var3 = var1 * var2;
	var4 = ((((int32_t)dig_H6) << 7) + ((T * (int32_t) dig_H7) / ((int32_t)100))) >> 4;
	var5 = ((var3 >> 14) * (var3 >> 14)) >> 10;
	var6 = (var4 * var5) >> 1;

	H = (var3 + var6) >> 12;

	if (H > 102400) H = 102400; // check for over- and under-flow
	else if(H < 0) H = 0;

	return (H / 1024.);
}


float DFRobot_BME680::readPressure(void)
{	
	uint32_t pressure = 0;
	uint8_t rawData[3];  // 20-bit pressure register data stored here
	this->readReg(BME680_FIELD_0_PRESS_MSB, 3, &rawData[0]);  
	pressure = (uint32_t) (((uint32_t) rawData[0] << 16 | (uint32_t) rawData[1] << 8 | rawData[2]) >> 4);

	int32_t var1 = 0, var2 = 0, var3 = 0, var4 = 0, P = 0;
	var1 = (((int32_t) t_fine) >> 1) - 64000;
	var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * (int32_t) dig_P6) >> 2;
	var2 = var2 + ((var1 * (int32_t)dig_P5) << 1);
	var2 = (var2 >> 2) + ((int32_t) dig_P4 << 16);
	var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) * ((int32_t) dig_P3 << 5)) >> 3) + (((int32_t) dig_P2 * var1) >> 1);
	var1 = var1 >> 18;
	var1 = ((32768 + var1) * (int32_t) dig_P1) >> 15;
	P = 1048576 - pressure;
	P = (int32_t)((P - (var2 >> 12)) * ((uint32_t)3125));
	var4 = (1 << 31);

	if(P >= var4)
		P = (( P / (uint32_t) var1) << 1);
	else
		P = ((P << 1) / (uint32_t) var1);
		
	var1 = ((int32_t) dig_P9 * (int32_t) (((P >> 3) * (P >> 3)) >> 13)) >> 12;
	var2 = ((int32_t)(P >> 2) * (int32_t) dig_P8) >> 13;
	var3 = ((int32_t)(P >> 8) * (int32_t)(P >> 8) * (int32_t)(P >> 8) * (int32_t)dig_P10) >> 17;
	P = (int32_t)(P) + ((var1 + var2 + var3 + ((int32_t)dig_P7 << 7)) >> 4);
	this->pressure = P;
	return P;
}


uint16_t DFRobot_BME680::readGas(void)
{	
	uint16_t gas = 0;
	uint8_t rawData[2];  // 10-bit gas resistance register data stored here
	this->readReg(BME680_FIELD_0_GAS_RL_MSB, 2, &rawData[0]);
	gas = (uint16_t) (((uint16_t) rawData[0] << 2 | (0xC0 & rawData[1]) >> 6) );

	// uint8_t var = 0;
	// readReg(BME680_FIELD_0_GAS_RL_LSB, 1, &var);
	// uint8_t gasRange = var & 0x0F;
	// double var1 = 0, gas_switch_error = 1.0;
	// var1 =  (1340.0 + 5.0 * gas_switch_error) * const_array1[gasRange];
	// float gas_res = var1 * const_array2[gasRange] / (gas - 512.0 + var1);
	return gas;
}


// Returns register code to be written to register BME680_RES_HEAT_CTRL for a user specified target temperature TT
// where TT is the target temperature in degrees Celsius
uint8_t DFRobot_BME680::TT(uint16_t TT)
{
	uint8_t res_heat_x = 0;
	double var1 = 0.0, var2 = 0.0, var3 = 0.0, var4 = 0.0, var5 = 0.0;
	uint8_t tempVar1 = 0, tempVar2 = 0;
	this->readReg(0xec, 1, &tempVar1);
	this->readReg(0xeb, 1, &tempVar2);
	uint16_t par_g1 = ((uint16_t) tempVar1 << 8) | tempVar2;
	this->readReg(0xed, 1, &tempVar1);
	uint8_t  par_g2 = tempVar1;
	this->readReg(0xee, 1, &tempVar1);
	uint8_t  par_g3 = tempVar1;
	this->readReg(0x02, 1, &tempVar1);
	uint8_t  res_heat_range = (tempVar1 & 0x30) >> 4;
	this->readReg(0x00, 1, &tempVar1);
	uint8_t res_heat_val = tempVar1;
	var1 = ((double) par_g1/ 16.0) + 49.0;
	var2 = (((double)par_g2 / 32768.0) * 0.0005) + 0.00235;
	var3 = (double)par_g3 / 1024.0;
	var4 = var1 * (1.0 + (var2 * (double)TT));
	var5 = var4 + (var3 * 25.0); // use 25 C as ambient temperature
	res_heat_x = (uint8_t)(((var5 * (4.0/(4.0 * (double)res_heat_range))) - 25.0) * 3.4 / ((res_heat_val * 0.002) + 1));
	return res_heat_x;
}


float BME680::readAltitude(void)
{	
	return (1000.0 * (101325 - this->pressure) / 3386.3752577878);
}

