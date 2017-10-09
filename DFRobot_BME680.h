#ifndef _DFRobot_BME680_h
#define _DFRobot_BME680_h

#include "Arduino.h"

#define BME680_CALIB_DATA00             0x00   // eight bytes of device-specific calibration data 0x00 - 0x07
#define BME680_FIELD_0_MEAS_STATUS_0    0x1D
#define BME680_FIELD_0_MEAS_STATUS_1    0x1E
#define BME680_FIELD_0_PRESS_MSB        0x1F
#define BME680_FIELD_0_PRESS_LSB        0x20
#define BME680_FIELD_0_PRESS_XLSB       0x21
#define BME680_FIELD_0_TEMP_MSB         0x22
#define BME680_FIELD_0_TEMP_LSB         0x23
#define BME680_FIELD_0_TEMP_XLSB        0x24
#define BME680_FIELD_0_HUM_MSB          0x25
#define BME680_FIELD_0_HUM_LSB          0x26

#define BME680_FIELD_0_GAS_RL_MSB       0x2A
#define BME680_FIELD_0_GAS_RL_LSB       0x2B

#define BME680_FIELD_1_MEAS_STATUS_0    0x2E
#define BME680_FIELD_1_MEAS_STATUS_1    0x2F
#define BME680_FIELD_1_PRESS_MSB        0x30
#define BME680_FIELD_1_PRESS_LSB        0x31
#define BME680_FIELD_1_PRESS_XLSB       0x32
#define BME680_FIELD_1_TEMP_MSB         0x33
#define BME680_FIELD_1_TEMP_LSB         0x34
#define BME680_FIELD_1_TEMP_XLSB        0x35
#define BME680_FIELD_1_HUM_MSB          0x36
#define BME680_FIELD_1_HUM_LSB          0x37

#define BME680_FIELD_2_GAS_RL_MSB       0x3B
#define BME680_FIELD_2_GAS_RL_LSB       0x3C

#define BME680_FIELD_2_MEAS_STATUS_0    0x3F
#define BME680_FIELD_2_MEAS_STATUS_1    0x40
#define BME680_FIELD_2_PRESS_MSB        0x41
#define BME680_FIELD_2_PRESS_LSB        0x42
#define BME680_FIELD_2_PRESS_XLSB       0x43
#define BME680_FIELD_2_TEMP_MSB         0x44
#define BME680_FIELD_2_TEMP_LSB         0x45
#define BME680_FIELD_2_TEMP_XLSB        0x46
#define BME680_FIELD_2_HUM_MSB          0x47
#define BME680_FIELD_2_HUM_LSB          0x48

#define BME680_FIELD_2_GAS_RL_MSB       0x4C
#define BME680_FIELD_2_GAS_RL_LSB       0x4D

#define BME680_IDAC_HEAT_X              0x50 // 10 IDAC byte values 0x50 - 0x59
#define BME680_RES_HEAT_X               0x5A // 10 RES byte values  0x5A - 0x63
#define BME680_GAS_WAIT_X               0x64 // 10 WAIT byte values 0x64 - 0x6D
#define BME680_GAS_WAIT_SHARED          0x6E  
#define BME680_RES_HEAT_CTRL            0x6F  
#define BME680_CTRL_GAS_0               0x70  
#define BME680_CTRL_GAS_1               0x71  
#define BME680_CTRL_HUM                 0x72  
#define BME680_STATUS                   0x73  
#define BME680_CTRL_MEAS                0x74  
#define BME680_CONFIG                   0x75  
#define BME680_CTRL_PROG                0x76  

#define BME680_CALIB_DATA_80            0x80  // more calibration data 0x80 - 0xA1

#define BME680_CALIB_DATA_E1            0xE1  // more calibration data 0xE1 - 0xF0

//#define BME680_CTRL_HUM                 0xF2
#define BME680_SPI_MEM_PAGE             0xF3   

#define BME680_CALIB_ADDR_1             0x89  // 25 bytes of calibration data for I2C
#define BME680_CALIB_ADDR_2             0xE1  // 16 bytes of calibration data for I2C

#define BME680_SEALEVEL                 1013.25f


#define SerialDebug true  // set to true to get Serial output for debugging

enum Posr {
  P_OSR_00 = 0,  // no op
  P_OSR_01,
  P_OSR_02,
  P_OSR_04,
  P_OSR_08,
  P_OSR_16
};

enum Hosr {
  H_OSR_00 = 0,  // no op
  H_OSR_01,
  H_OSR_02,
  H_OSR_04,
  H_OSR_08,
  H_OSR_16
};

enum Tosr {
  T_OSR_00 = 0,  // no op
  T_OSR_01,
  T_OSR_02,
  T_OSR_04,
  T_OSR_08,
  T_OSR_16
};

enum IIRFilter {
  full = 0,  // bandwidth at full sample rate
  BW0_223ODR,
  BW0_092ODR,
  BW0_042ODR,
  BW0_021ODR // bandwidth at 0.021 x sample rate
};

enum Mode {
  BME680Sleep = 0,
  Forced,
  Parallel,
  Sequential
};

enum SBy {
  t_00_6ms = 0,
  t_62_5ms,
  t_125ms,
  t_250ms,
  t_500ms,
  t_1000ms,
  t_10ms,
  t_20ms,
};

enum GWaitMult {
  gw_1xmult = 0,
  gw_4xmult,
  gw_16xmult,
  gw_64xmult
};


class DFRobot_BME680
{
  public:
    bool        begin(void);
    float       readTempture(void);
    float       readHumidity(void);
    float       readPressure(void);
    float       readGas(void);
    float       readAltitude(void);
    void        startConvert(void);
    float       readGasResistance(void);
    float       readSeaLevel(float altitude);
    
  public:
    uint8_t       TT(uint16_t tt);
    
    virtual void        readReg(uint8_t addr, uint8_t count, uint8_t* pBuf) = 0;
    virtual void        writeReg(uint8_t addr, uint8_t dat) = 0;
    virtual uint8_t     readID(void) = 0;
};

#endif
