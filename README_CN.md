# DFRobot_BME680

* [English Version](./README.md)

BME680 是专为移动应用和可穿戴设备开发的集成环境传感器其中尺寸和低功耗是关键要求。 BME680 扩展了 Bosch Sensortec <br>
现有的环境传感器系列，首次集成了用于气体、压力、湿度和温度的单个高线性度和高精度传感器。<br>

![产品效果图](./resources/images/SEN0248.png) 

## 产品链接（[https://www.dfrobot.com.cn/goods-1621.html](https://www.dfrobot.com.cn/goods-1621.html)）
    SKU: SEN0248

## 目录

  * [概述](#概述)
  * [库安装](#库安装)
  * [方法](#方法)
  * [兼容性](#兼容性)
  * [历史](#历史)
  * [创作者](#创作者)

## 概述

提供一个 Arduino 库，用于通过 I2C 通过 SPI 读取和解释 Bosch BME680 数据。读取温度、湿度、气体、IAQ（示例\自述文件中的详细信息）、压力并计算高度。

## 库安装

这里有2种安装方法：
1. 使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。
2. 直接在Arduino软件库管理中搜索下载 DFRobot_AHT20 库


## 方法
```C++
  /**
   * @fn begin
   * @brief 初始化BME680传感器设备
   * @return 结果
   * @retval  非0值 : 失败
   * @retval  0     : 成功
   */
  int16_t begin(void);

  /**
   * @fn update
   * @brief 将所有数据更新到 MCU 内存
   */
  void    update(void);

  /**
   * @fn iaqUpdate
   * @brief 使用 IAQ 将所有数据更新到 MCU ram（现在仅适用于 esp8266）
   *
   * @return 更新状态:
   * @retval 0 :完成
   * @retval 1 :正在忙
   */
  int8_t  iaqUpdate(void);

  /**
   * @fn startConvert
   * @brief 开始转换以获得准确的值
   */
  void  startConvert(void);
  /**
   * @fn readTemperature
   * @brief 获取温度值 (单位 摄氏度)
   *
   * @return 温度值, 这个值有两个小数点
   */
  float readTemperature(void);
  /**
   * @fn readPressure
   * @brief 读取压强值 (单位 帕)
   *
   * @return 压强值, 这个值有两个小数点
   */
  float readPressure(void);
  /**
   * @fn readHumidity
   * @brief 读取湿度值 (单位 %rh)
   * @return 湿度值, 这个值有两个小数点
   */
  float readHumidity(void);
  /**
   * @fn readAltitude
   * @brief 读取高度（单位米）
   * @return 高度值, 这个值有两个小数点
   */
  float readAltitude(void);
  /**
   * @fn readCalibratedAltitude
   * @brief 读取校准高度（单位米）
   *
   * @param seaLevel  正规化大气压
   *
   * @return 标定高度值，该值有两位小数
   */
  float readCalibratedAltitude(float seaLevel);
  /**
   * @fn readGasResistance
   * @brief 读取气体电阻（单位欧姆）
   * @return 温度值，这个值有两位小数
   */
  float readGasResistance(void);
  /**
   * @fn readSeaLevel
   * @brief 读取标准化大气压力（单位帕）
   * @param altitude   标准化大气压力
   * @return 标准化大气压力
   */
  float readSeaLevel(float altitude);
  /**
   * @fn readIAQ
   * @brief 读 IAQ
   * @return 返回 IAQ的值
   */
  float readIAQ(void);
  /**
   * @fn setParam
   * @brief 设置bme680的参数
   *
   * @param eParam        : 需要设置的参数
   *        dat           : 对象数据，不能超过5
   */  
  void    setParam(eBME680_param_t eParam, uint8_t dat);
  /**
   * @fn setGasHeater
   * @brief 设置bme680燃气加热器
   * @param temp        :目标温度
   * @param t           :以毫秒为单位花费的时间
   */
   void    setGasHeater(uint16_t temp, uint16_t t);
  /**
   * @fn isIAQReady
   * @brief 检测 IAQ 是否准备好
   * @return result:
   * @retval 0 :准备完成
   * @retval 1 :繁忙中
   */
  uint8_t isIAQReady(void);

```

## 兼容性

MCU                | Work Well | Work Wrong | Untested  | Remarks
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266  |      √       |             |            | 
FireBeetle-BLE4.1 |       √      |             |            | 
Arduino uno |       √      |             |            | 
Arduino leonardo |      √       |             |            | 

## 历史
- 2017/12/04 - 2.0.0 版本
- 2017/09/04 - 1.0.0 版本

## 创作者

Written by Frank(jiehan.guo@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))





