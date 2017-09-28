#ifndef _DFRobot_BME680_I2C_h
#define _DFRobot_BME680_I2C_h

#include "Arduino.h"
#include "Wire.h"
#include "DFRobot_BME680.h"

#define BME680_ID                       0xD0  //should return 0x61
#define BME680_RESET                    0xE0      


class DFRobot_BME680_I2C : public DFRobot_BME680
{
  public:
    DFRobot_BME680_I2C(uint8_t addr);
    
  public:
    uint8_t       I2C_addr;
    
    void          readReg(uint8_t addr, uint8_t count, uint8_t* pBuf);
    void          writeReg(uint8_t addr, uint8_t dat);
    uint8_t       readID(void);
};

#endif
