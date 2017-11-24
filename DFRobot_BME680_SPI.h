#ifndef DFROBOT_BME680_SPI_H
#define DFROBOT_BME680_SPI_H

#include "DFRobot_BME680.h"

class DFRobot_BME680_SPI : public DFRobot_BME680
{
  public:
    DFRobot_BME680_SPI(uint8_t pin_cs);
};

#endif