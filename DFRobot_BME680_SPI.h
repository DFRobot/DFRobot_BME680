#ifndef _DFRobot_BME680_SPI_h
#define _DFRobot_BME680_SPI_h

#include "Arduino.h"
#include "SPI.h"
#include "DFRobot_BME680.h"

#define BME680_ID                       0x50  //should return 0x61
#define BME680_RESET                    0x60   


class DFRobot_BME680_SPI : public DFRobot_BME680
{
  public:
    DFRobot_BME680_SPI(uint8_t pin_cs);
    
  public:
    uint8_t       pin_cs;
    
    void          readReg(uint8_t addr, uint8_t count, uint8_t* pBuf);
    void          writeReg(uint8_t addr, uint8_t dat);
    uint8_t       readID(void);
};

#endif

