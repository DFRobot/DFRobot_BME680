/**
 * @file DFRobot_BME680_I2C.h
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef DFRobot_BME680_I2C_H
#define DFRobot_BME680_I2C_H

#include "DFRobot_BME680.h"


class DFRobot_BME680_I2C : public DFRobot_BME680
{
  public:
    DFRobot_BME680_I2C(uint8_t I2CAddr);

    void        setConvertAndUpdate(void);
};

#endif