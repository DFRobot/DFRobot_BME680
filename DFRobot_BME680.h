#ifndef DFROBOT_BME680_H
#define DFROBOT_BME680_H

#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"

#define BME680_SEALEVEL 1013.25f

/**\name C standard macros */
#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
#define NULL   ((void *) 0)
#endif
#endif

/** BME680 General config */
#define BME680_POLL_PERIOD_MS		(10)

/** BME680 I2C addresses */
#define BME680_I2C_ADDR_PRIMARY		(0x76)
#define BME680_I2C_ADDR_SECONDARY	(0x77)

/** BME680 unique chip identifier */
#define BME680_CHIP_ID  (0x61)

/** BME680 coefficients related defines */
#define BME680_COEFF_SIZE		(0x41)
#define BME680_COEFF_ADDR1_LEN		(25)
#define BME680_COEFF_ADDR2_LEN		(16)

/** BME680 field_x related defines */
#define BME680_FIELD_LENGTH		(15)
#define BME680_FIELD_ADDR_OFFSET	(17)

/** Soft reset command */
#define BME680_SOFT_RESET_CMD   (0xb6)

/** Error code definitions */
#define BME680_OK		(0)
/* Errors */
#define BME680_E_NULL_PTR		    (-1)
#define BME680_E_COM_FAIL		    (-2)
#define BME680_E_DEV_NOT_FOUND		(-3)
#define BME680_E_INVALID_LENGTH		(-4)

/* Warnings */
#define BME680_W_DEFINE_PWR_MODE	(1)
#define BME680_W_NO_NEW_DATA        (2)

/* Info's */
#define BME680_I_MIN_CORRECTION		(1)
#define BME680_I_MAX_CORRECTION		(2)

/** Register map */
/** Other coefficient's address */
#define BME680_ADDR_RES_HEAT_VAL_ADDR	(0x00)
#define BME680_ADDR_RES_HEAT_RANGE_ADDR	(0x02)
#define BME680_ADDR_RANGE_SW_ERR_ADDR	(0x04)
#define BME680_ADDR_SENS_CONF_START	(0x5A)
#define BME680_ADDR_GAS_CONF_START	(0x64)

/** Field settings */
#define BME680_FIELD0_ADDR		(0x1d)

/** Heater settings */
#define BME680_RES_HEAT0_ADDR		(0x5a)
#define BME680_GAS_WAIT0_ADDR		(0x64)

/** Sensor configuration registers */
#define BME680_CONF_HEAT_CTRL_ADDR		(0x70)
#define BME680_CONF_ODR_RUN_GAS_NBC_ADDR	(0x71)
#define BME680_CONF_OS_H_ADDR			(0x72)
#define BME680_MEM_PAGE_ADDR			(0xf3)
#define BME680_CONF_T_P_MODE_ADDR		(0x74)
#define BME680_CONF_ODR_FILT_ADDR		(0x75)

/** Coefficient's address */
#define BME680_COEFF_ADDR1	(0x89)
#define BME680_COEFF_ADDR2	(0xe1)

/** Chip identifier */
#define BME680_CHIP_ID_ADDR	(0xd0)

/** Soft reset register */
#define BME680_SOFT_RESET_ADDR		(0xe0)

/** Heater control settings */
#define BME680_ENABLE_HEATER		(0x00)
#define BME680_DISABLE_HEATER		(0x08)

/** Gas measurement settings */
#define BME680_DISABLE_GAS_MEAS		(0x00)
#define BME680_ENABLE_GAS_MEAS		(0x01)

/** Over-sampling settings */
#define BME680_OS_NONE		(0)
#define BME680_OS_1X		(1)
#define BME680_OS_2X		(2)
#define BME680_OS_4X		(3)
#define BME680_OS_8X		(4)
#define BME680_OS_16X		(5)

/** IIR filter settings */
#define BME680_FILTER_SIZE_0	(0)
#define BME680_FILTER_SIZE_1	(1)
#define BME680_FILTER_SIZE_3	(2)
#define BME680_FILTER_SIZE_7	(3)
#define BME680_FILTER_SIZE_15	(4)
#define BME680_FILTER_SIZE_31	(5)
#define BME680_FILTER_SIZE_63	(6)
#define BME680_FILTER_SIZE_127	(7)

/** Power mode settings */
#define BME680_SLEEP_MODE	(0)
#define BME680_FORCED_MODE	(1)

/** Delay related macro declaration */
#define BME680_RESET_PERIOD		(10)

/** SPI memory page settings */
#define BME680_MEM_PAGE0	(0x10)
#define BME680_MEM_PAGE1	(0x00)

/** Ambient humidity shift value for compensation */
#define BME680_HUM_REG_SHIFT_VAL	(4)

/** Run gas enable and disable settings */
#define BME680_RUN_GAS_DISABLE	(0)
#define BME680_RUN_GAS_ENABLE	(1)

/** Buffer length macro declaration */
#define BME680_TMP_BUFFER_LENGTH	(40)
#define BME680_REG_BUFFER_LENGTH	(6)
#define BME680_FIELD_DATA_LENGTH	(3)
#define BME680_GAS_REG_BUF_LENGTH	(20)
#define BME680_GAS_HEATER_PROF_LEN_MAX  (10)

/** Settings selector */
#define BME680_OST_SEL			(1)
#define BME680_OSP_SEL			(2)
#define BME680_OSH_SEL			(4)
#define BME680_GAS_MEAS_SEL		(8)
#define BME680_FILTER_SEL		(16)
#define BME680_HCNTRL_SEL		(32)
#define BME680_RUN_GAS_SEL		(64)
#define BME680_NBCONV_SEL		(128)
#define BME680_GAS_SENSOR_SEL		(BME680_GAS_MEAS_SEL | BME680_RUN_GAS_SEL | BME680_NBCONV_SEL)

/** Number of conversion settings*/
#define BME680_NBCONV_MIN		(0)
#define BME680_NBCONV_MAX		(10)

/** Mask definitions */
#define BME680_GAS_MEAS_MSK	(0x30)
#define BME680_NBCONV_MSK	(0X0F)
#define BME680_FILTER_MSK	(0X1C)
#define BME680_OST_MSK		(0XE0)
#define BME680_OSP_MSK		(0X1C)
#define BME680_OSH_MSK		(0X07)
#define BME680_HCTRL_MSK	(0x08)
#define BME680_RUN_GAS_MSK	(0x10)
#define BME680_MODE_MSK		(0x03)
#define BME680_RHRANGE_MSK	(0x30)
#define BME680_RSERROR_MSK	(0xf0)
#define BME680_NEW_DATA_MSK	(0x80)
#define BME680_GAS_INDEX_MSK	(0x0f)
#define BME680_GAS_RANGE_MSK	(0x0f)
#define BME680_GASM_VALID_MSK	(0x20)
#define BME680_HEAT_STAB_MSK	(0x10)
#define BME680_MEM_PAGE_MSK	(0x10)
#define BME680_SPI_RD_MSK	(0x80)
#define BME680_SPI_WR_MSK	(0x7f)
#define	BME680_BIT_H1_DATA_MSK	(0x0F)

/** Bit position definitions for sensor settings */
#define BME680_GAS_MEAS_POS	(4)
#define BME680_FILTER_POS	(2)
#define BME680_OST_POS		(5)
#define BME680_OSP_POS		(2)
#define BME680_RUN_GAS_POS	(4)

/** Array Index to Field data mapping for Calibration Data*/
#define BME680_T2_LSB_REG	(1)
#define BME680_T2_MSB_REG	(2)
#define BME680_T3_REG		(3)
#define BME680_P1_LSB_REG	(5)
#define BME680_P1_MSB_REG	(6)
#define BME680_P2_LSB_REG	(7)
#define BME680_P2_MSB_REG	(8)
#define BME680_P3_REG		(9)
#define BME680_P4_LSB_REG	(11)
#define BME680_P4_MSB_REG	(12)
#define BME680_P5_LSB_REG	(13)
#define BME680_P5_MSB_REG	(14)
#define BME680_P7_REG		(15)
#define BME680_P6_REG		(16)
#define BME680_P8_LSB_REG	(19)
#define BME680_P8_MSB_REG	(20)
#define BME680_P9_LSB_REG	(21)
#define BME680_P9_MSB_REG	(22)
#define BME680_P10_REG		(23)
#define BME680_H2_MSB_REG	(25)
#define BME680_H2_LSB_REG	(26)
#define BME680_H1_LSB_REG	(26)
#define BME680_H1_MSB_REG	(27)
#define BME680_H3_REG		(28)
#define BME680_H4_REG		(29)
#define BME680_H5_REG		(30)
#define BME680_H6_REG		(31)
#define BME680_H7_REG		(32)
#define BME680_T1_LSB_REG	(33)
#define BME680_T1_MSB_REG	(34)
#define BME680_GH2_LSB_REG	(35)
#define BME680_GH2_MSB_REG	(36)
#define BME680_GH1_REG		(37)
#define BME680_GH3_REG		(38)

/** BME680 register buffer index settings*/
#define BME680_REG_FILTER_INDEX		(5)
#define BME680_REG_TEMP_INDEX		(4)
#define BME680_REG_PRES_INDEX		(4)
#define BME680_REG_HUM_INDEX		(2)
#define BME680_REG_NBCONV_INDEX		(1)
#define BME680_REG_RUN_GAS_INDEX	(1)
#define BME680_REG_HCTRL_INDEX		(0)

/** Macro to combine two 8 bit data's to form a 16 bit data */
#define BME680_CONCAT_BYTES(msb, lsb)	(((uint16_t)msb << 8) | (uint16_t)lsb)

/** Macro to SET and GET BITS of a register */
#define BME680_SET_BITS(reg_data, bitname, data) \
		((reg_data & ~(bitname##_MSK)) | \
		((data << bitname##_POS) & bitname##_MSK))
#define BME680_GET_BITS(reg_data, bitname)	((reg_data & (bitname##_MSK)) >> \
	(bitname##_POS))

/** Macro variant to handle the bitname position if it is zero */
#define BME680_SET_BITS_POS_0(reg_data, bitname, data) \
				((reg_data & ~(bitname##_MSK)) | \
				(data & bitname##_MSK))
#define BME680_GET_BITS_POS_0(reg_data, bitname)  (reg_data & (bitname##_MSK))

/** Type definitions */
/*
 * Generic communication function pointer
 * @param[in] dev_id: Place holder to store the id of the device structure
 * 						Can be used to store the index of the Chip select or
 * 						I2C address of the device.
 * @param[in] reg_addr:	Used to select the register the where data needs to
 * 						be read from or written to.
 * @param[in/out] reg_data: Data array to read/write
 * @param[in] len: Length of the data array
 */
typedef int8_t (*bme680_com_fptr_t)(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);

/*
 * Delay function pointer
 * @param[in] period: Time period in milliseconds
 */
typedef void (*bme680_delay_fptr_t)(uint32_t period);

/*!
 * @brief Interface selection Enumerations
 */
enum bme680_intf {
	/*! SPI interface */
	BME680_SPI_INTF,
	/*! I2C interface */
	BME680_I2C_INTF
};

/* structure definitions */
/*!
 * @brief Sensor field data structure
 */
struct	bme680_field_data {
	/*! Contains new_data, gasm_valid & heat_stab */
	uint8_t status;
	/*! The index of the heater profile used */
	uint8_t gas_index;
	/*! Measurement index to track order */
	uint8_t meas_index;
	/*! Temperature in degree celsius x100 */
	float temperature;
	/*! Pressure in Pascal */
	float pressure;
	/*! Humidity in % relative humidity x1000 */
	float humidity;
	/*! Gas resistance in Ohms */
	float gas_resistance;
  /*! Gas */
  uint16_t gas;
  /*! Altitude */
  float altitude;
  /*! Sea level pressure */
  float seaLevel;
};

/*!
 * @brief Structure to hold the Calibration data
 */
struct	bme680_calib_data {
	/*! Variable to store calibrated humidity data */
	uint16_t par_h1;
	/*! Variable to store calibrated humidity data */
	uint16_t par_h2;
	/*! Variable to store calibrated humidity data */
	int8_t par_h3;
	/*! Variable to store calibrated humidity data */
	int8_t par_h4;
	/*! Variable to store calibrated humidity data */
	int8_t par_h5;
	/*! Variable to store calibrated humidity data */
	uint8_t par_h6;
	/*! Variable to store calibrated humidity data */
	int8_t par_h7;
	/*! Variable to store calibrated gas data */
	int8_t par_gh1;
	/*! Variable to store calibrated gas data */
	int16_t par_gh2;
	/*! Variable to store calibrated gas data */
	int8_t par_gh3;
	/*! Variable to store calibrated temperature data */
	uint16_t par_t1;
	/*! Variable to store calibrated temperature data */
	int16_t par_t2;
	/*! Variable to store calibrated temperature data */
	int8_t par_t3;
	/*! Variable to store calibrated pressure data */
	uint16_t par_p1;
	/*! Variable to store calibrated pressure data */
	int16_t par_p2;
	/*! Variable to store calibrated pressure data */
	int8_t par_p3;
	/*! Variable to store calibrated pressure data */
	int16_t par_p4;
	/*! Variable to store calibrated pressure data */
	int16_t par_p5;
	/*! Variable to store calibrated pressure data */
	int8_t par_p6;
	/*! Variable to store calibrated pressure data */
	int8_t par_p7;
	/*! Variable to store calibrated pressure data */
	int16_t par_p8;
	/*! Variable to store calibrated pressure data */
	int16_t par_p9;
	/*! Variable to store calibrated pressure data */
	uint8_t par_p10;
	/*! Variable to store t_fine size */
	int32_t t_fine;
	/*! Variable to store heater resistance range */
	uint8_t res_heat_range;
	/*! Variable to store heater resistance value */
	int8_t res_heat_val;
	/*! Variable to store error range */
	int8_t range_sw_err;
};

/*!
 * @brief BME680 sensor settings structure which comprises of ODR,
 * over-sampling and filter settings.
 */
struct	bme680_tph_sett {
	/*! Humidity oversampling */
	uint8_t os_hum;
	/*! Temperature oversampling */
	uint8_t os_temp;
	/*! Pressure oversampling */
	uint8_t os_pres;
	/*! Filter coefficient */
	uint8_t filter;
};

/*!
 * @brief BME680 gas sensor which comprises of gas settings
 *  and status parameters
 */
struct	bme680_gas_sett {
	/*! Variable to store nb conversion */
	uint8_t nb_conv;
	/*! Variable to store heater control */
	uint8_t heatr_ctrl;
	/*! Run gas enable value */
	uint8_t run_gas;
	/*! Pointer to store heater temperature */
	uint16_t heatr_temp;
	/*! Pointer to store duration profile */
	uint16_t heatr_dur;
};

/*!
 * @brief BME680 device structure
 */
struct	bme680_dev {
	/*! Chip Id */
	uint8_t chip_id;
	/*! Device Id */
	uint8_t dev_id;
	/*! SPI/I2C interface */
	enum bme680_intf intf;
	/*! Memory page used */
	uint8_t mem_page;
	/*! Ambient temperature in Degree C*/
	int8_t amb_temp;
	/*! Sensor calibration data */
	struct bme680_calib_data calib;
	/*! Sensor settings */
	struct bme680_tph_sett tph_sett;
	/*! Gas Sensor settings */
	struct bme680_gas_sett gas_sett;
	/*! Sensor power modes */
	uint8_t power_mode;
	/*! New sensor fields */
	uint8_t new_fields;
	/*! Store the info messages */
	uint8_t info_msg;
	/*! Burst read structure */
	bme680_com_fptr_t read;
	/*! Burst write structure */
	bme680_com_fptr_t write;
	/*! Delay in ms */
	bme680_delay_fptr_t delay_ms;
	/*! Communication function result */
	int8_t com_rslt;
};

enum eBME680_INTERFACE {
  eBME680_INTERFACE_SPI,
  eBME680_INTERFACE_I2C
};


int8_t bme680_init(struct bme680_dev *dev);
int8_t bme680_set_regs(const uint8_t *reg_addr, const uint8_t *reg_data, uint8_t len, struct bme680_dev *dev);
int8_t bme680_get_regs(uint8_t reg_addr, uint8_t *reg_data, uint16_t len, struct bme680_dev *dev);
int8_t bme680_soft_reset(struct bme680_dev *dev);
int8_t bme680_set_sensor_mode(struct bme680_dev *dev);
int8_t bme680_get_sensor_mode(struct bme680_dev *dev);
void bme680_set_profile_dur(uint16_t duration, struct bme680_dev *dev);
void bme680_get_profile_dur(uint16_t *duration, struct bme680_dev *dev);
int8_t bme680_get_sensor_data(struct bme680_field_data *data, struct bme680_dev *dev);
int8_t bme680_set_sensor_settings(uint16_t desired_settings, struct bme680_dev *dev);
int8_t bme680_get_sensor_settings(uint16_t desired_settings, struct bme680_dev *dev);


class DFRobot_BME680
{
  public:
    DFRobot_BME680(bme680_com_fptr_t readReg, bme680_com_fptr_t writeReg, bme680_delay_fptr_t delayMS, eBME680_INTERFACE interface);

    uint8_t       bme680_I2CAddr = 0;

    boolean       begin(void);
    void          update(void);
    void          startConvert(void);
    float         readTempture(void);
    float         readPressure(void);
    float         readHumidity(void);
    float         readAltitude(void);
    uint16_t      readGas(void);
    float         readGasResistance(void);
    float         readSeaLevel(float altitude);
};

#endif


