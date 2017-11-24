#ifndef DFRobot_BME680_I2C_H
#define DFRobot_BME680_I2C_H

#include "DFRobot_BME680.h"


class DFRobot_BME680_I2C : public DFRobot_BME680
{
  public:
    DFRobot_BME680_I2C(uint8_t I2CAddr);
};

#endif