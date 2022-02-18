/**
 * @file DFRobot_BME680_SPI.h
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */

#ifndef DFROBOT_BME680_SPI_H
#define DFROBOT_BME680_SPI_H

#include "DFRobot_BME680.h"

class DFRobot_BME680_SPI : public DFRobot_BME680
{
  public:
    DFRobot_BME680_SPI(uint8_t pin_cs);

    void        setConvertAndUpdate(void);
};

#endif