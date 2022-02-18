/**
 * @file bsec_interface.h
 * @brief Contains the API for BSEC
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author Frank(jiehan.guo@dfrobot.com)
 * @version  V1.0
 * @date  2017-12-04
 * @url https://github.com/DFRobot/DFRobot_BME680
 */


#ifndef __BSEC_INTERFACE_H__
#define __BSEC_INTERFACE_H__

#include "bsec_datatypes.h"

#ifdef __cplusplus
 extern "C" {
#endif

/**
 * @fn bsec_get_version
 * @brief Return the version information of BSEC library
 * @param     bsec_version_p      pointer to struct which is to be populated with the version information
 * @return Zero if successful, otherwise an error code
 */

bsec_library_return_t bsec_get_version(bsec_version_t * bsec_version_p);

/**
 * @brief Initialize the library
 *
 * @n Initialization and reset of BSEC is performed by calling bsec_init(). Calling this function sets up the relation 
 * @n among all internal modules, initializes run-time dependent library states and resets the configuration and state
 * @n of all BSEC signal processing modules to defaults.
 * 
 * @n Before any further use, the library must be initialized. This ensure that all memory and states are in defined
 * @n conditions prior to processing any data.
 *
 * @return Zero if successful, otherwise an error code
 */
bsec_library_return_t bsec_init(void);

/**
 * @fn bsec_update_subscription
 * @brief Subscribe to library virtual sensors outputs
 *
 * @n Use bsec_update_subscription() to instruct BSEC which of the processed output signals are requested at which sample rates.
 * @n See ::bsec_virtual_sensor_t for available library outputs. 
 *
 * @n Based on the requested virtual sensors outputs, BSEC will provide information about the required physical sensor input signals 
 * @n (see ::bsec_physical_sensor_t) with corresponding sample rates. This information is purely informational as bsec_sensor_control()
 * @n will ensure the sensor is operated in the required manner. To disable a virtual sensor, set the sample rate to BSEC_SAMPLE_RATE_DISABLED.
 *
 * @n The subscription update using bsec_update_subscription() is apart from the signal processing one of the the most 
 * @n important functions. It allows to enable the desired library outputs. The function determines which physical input 
 * @n sensor signals are required at which sample rate to produce the virtual output sensor signals requested by the user. 
 * @n When this function returns with success, the requested outputs are called subscribed. A very important feature is the 
 * @n retaining of already subscribed outputs. Further outputs can be requested or disabled both individually and 
 * @n group-wise in addition to already subscribed outputs without changing them unless a change of already subscribed 
 * @n outputs is requested.
 *
 * @note The state of the library concerning the subscribed outputs cannot be retained among reboots.
 *
 * @n The interface of bsec_update_subscription() requires the usage of arrays of sensor configuration structures. 
 * @n Such a structure has the fields sensor identifier and sample rate. These fields have the properties:
 * @n  - Output signals of virtual sensors must be requested using unique identifiers (Member of ::bsec_virtual_sensor_t)
 * @n  - Different sets of identifiers are available for inputs of physical sensors and outputs of virtual sensors
 * @n  - Identifiers are unique values defined by the library, not from external
 * @n  - Sample rates must be provided as value of
 * @n  - An allowed sample rate for continuously sampled signals
 * @n  - 65535.0f (BSEC_SAMPLE_RATE_DISABLED) to turn off outputs and identify disabled inputs
 *
 * @note The same sensor identifiers are also used within the functions bsec_do_steps().
 *
 * @n The usage principles of bsec_update_subscription() are:
 * @n  - Differential updates (i.e., only asking for outputs that the user would like to change) is supported.
 * @n  - Invalid requests of outputs are ignored. Also if one of the requested outputs is unavailable, all the requests are ignored. At the same time, a warning is returned.
 * @n  - To disable BSEC, all outputs shall be turned off. Only enabled (subscribed) outputs have to be disabled while 
 * @n    already disabled outputs do not have to be disabled explicitly.
 *
 * @param requested_virtual_sensors       Pointer to array of requested virtual sensor (output) configurations for the library
 * @param n_requested_virtual_sensors     Number of virtual sensor structs pointed by requested_virtual_sensors
 * @param required_sensor_settings        Pointer to array of required physical sensor configurations for the library
 * @param n_required_sensor_settings      [in] Size of allocated required_sensor_settings array, [out] number of sensor configurations returned
 *
 * @return Zero when successful, otherwise an error code
 */
bsec_library_return_t bsec_update_subscription(const bsec_sensor_configuration_t * const requested_virtual_sensors,
                const uint8_t n_requested_virtual_sensors, bsec_sensor_configuration_t * required_sensor_settings,
                uint8_t * n_required_sensor_settings);


/*!
 * @brief Main signal processing function of BSEC
 *
 *
 * @n Processing of the input signals and returning of output samples is performed by bsec_do_steps().
 * @n - The samples of all library inputs must be passed with unique identifiers representing the input signals from 
 * @n   physical sensors where the order of these inputs can be chosen arbitrary. However, all input have to be provided 
 * @n   within the same time period as they are read. A sequential provision to the library might result in undefined 
 * @n   behaviour.
 * @n - The samples of all library outputs are returned with unique identifiers corresponding to the output signals of 
 * @n   virtual sensors where the order of the returned outputs may be arbitrary.
 * @n - The samples of all input as well as output signals of physical as well as virtual sensors use the same 
 * @n   representation in memory with the following fields:
 * @n - Sensor identifier:
 * @n   - For inputs: required to identify the input signal from a physical sensor
 * @n   - For output: overwritten by bsec_do_steps() to identify the returned signal from a virtual sensor
 * @n   - Time stamp of the sample
 * @n Calling bsec_do_steps() requires the samples of the input signals to be provided along with their time stamp when 
 * @n they are recorded and only when they are acquired. Repetition of samples with the same time stamp are ignored and 
 * @n result in a warning. Repetition of values of samples which are not acquired anew by a sensor result in deviations 
 * @n of the computed output signals. Concerning the returned output samples, an important feature is, that a value is 
 * @n returned for an output only when a new occurrence has been computed. A sample of an output signal is returned only 
 * @n once.
 *
 *
 * @param inputs          Array of input data samples. Each array element represents a sample of a different physical sensor.
 * @param n_inputs        Number of passed input data structs.
 * @param outputs         Array of output data samples. Each array element represents a sample of a different virtual sensor.
 * @param n_outputs       [in] Number of allocated output structs, [out] number of outputs returned
 *
 * @return Zero when successful, otherwise an error code
 */
 
bsec_library_return_t bsec_do_steps(const bsec_input_t * const inputs, const uint8_t n_inputs, bsec_output_t * outputs, uint8_t * n_outputs);


/**
 * @fn bsec_reset_output
 * @brief Reset a particular virtual sensor output
 *
 * @n This function allows specific virtual sensor outputs to be reset. The meaning of "reset" depends on the specific 
 * @n output. In case of the IAQ output, reset means zeroing the output to the current ambient conditions.
 *
 * @param sensor_id           Virtual sensor to be reset
 *
 * @return Zero when successful, otherwise an error code.
 */

bsec_library_return_t bsec_reset_output(uint8_t sensor_id);


/**
 * @brief Update algorithm configuration parameters
 *
 * @n BSEC uses a default configuration for the modules and common settings. The initial configuration can be customized 
 * @n by bsec_set_configuration(). This is an optional step.
 * 
 * @note A work buffer with sufficient size is required and has to be provided by the function caller to decompose 
 * @n the serialization and apply it to the library and its modules. Please use #BSEC_MAX_PROPERTY_BLOB_SIZE for allotting 
 * @n the required size.
 *
 * @param serialized_settings     Settings serialized to a binary blob
 * @param n_serialized_settings   Size of the settings blob
 * @param work_buffer             Work buffer used to parse the blob
 * @param n_work_buffer_size      Length of the work buffer available for parsing the blob
 *
 * @return Zero when successful, otherwise an error code.
 */

bsec_library_return_t bsec_set_configuration(const uint8_t * const serialized_settings,
                const uint32_t n_serialized_settings, uint8_t * work_buffer,
                const uint32_t n_work_buffer_size);


/**
 * @brief Restore the internal state of the library
 *
 * @n BSEC uses a default state for all signal processing modules and the BSEC module. To ensure optimal performance, 
 * @n especially of the gas sensor functionality, it is recommended to retrieve the state using bsec_get_state()
 * @n before unloading the library, storing it in some form of non-volatile memory, and setting it using bsec_set_state() 
 * @n before resuming further operation of the library.
 * 
 * @note A work buffer with sufficient size is required and has to be provided by the function caller to decompose the 
 * @n serialization and apply it to the library and its modules. Please use #BSEC_MAX_PROPERTY_BLOB_SIZE for allotting the 
 * @n required size.
 *
 * @param serialized_state        States serialized to a binary blob
 * @param n_serialized_state      Size of the state blob
 * @param work_buffer             Work buffer used to parse the blob
 * @param n_work_buffer_size      Length of the work buffer available for parsing the blob
 *
 * @return Zero when successful, otherwise an error code
 */

bsec_library_return_t bsec_set_state(const uint8_t * const serialized_state, const uint32_t n_serialized_state,
                uint8_t * work_buffer, const uint32_t n_work_buffer_size);


/**
 * @fn bsec_get_configuration
 * @brief Retrieve the current library configuration
 *
 * @n BSEC allows to retrieve the current configuration using bsec_get_configuration(). Returns a binary blob encoding 
 * @n the current configuration parameters of the library in a format compatible with bsec_set_configuration().
 *
 * @note The function bsec_get_configuration() is required to be used for debugging purposes only.
 * @note A work buffer with sufficient size is required and has to be provided by the function caller to decompose the 
 * @n serialization and apply it to the library and its modules. Please use #BSEC_MAX_PROPERTY_BLOB_SIZE for allotting the 
 * @n required size.
 * 
 *
 * @param config_id                   Identifier for a specific set of configuration settings to be returned;shall be zero to retrieve all configuration settings.                                           
 * @param serialized_settings         Buffer to hold the serialized config blob
 * @param n_serialized_settings_max   Maximum available size for the serialized settings
 * @param work_buffer                 Work buffer used to parse the binary blob
 * @param n_work_buffer               Length of the work buffer available for parsing the blob
 * @param n_serialized_settings       Actual size of the returned serialized configuration blob
 *
 * @return Zero when successful, otherwise an error code
 */

bsec_library_return_t bsec_get_configuration(const uint8_t config_id, uint8_t * serialized_settings, const uint32_t n_serialized_settings_max,
                uint8_t * work_buffer, const uint32_t n_work_buffer, uint32_t * n_serialized_settings);


/**
 * @fn bsec_get_state
 * @brief Retrieve the current internal library state
 *
 * @n BSEC allows to retrieve the current states of all signal processing modules and the BSEC module using 
 * @n bsec_get_state(). This allows a restart of the processing after a reboot of the system by calling bsec_set_state().
 * 
 * @note A work buffer with sufficient size is required and has to be provided by the function caller to decompose the 
 * @n serialization and apply it to the library and its modules. Please use #BSEC_MAX_PROPERTY_BLOB_SIZE for allotting the 
 * @n required size.
 * 
 *
 * @param state_set_id                Identifier for a specific set of states to be returned; shall be zero to retrieve all states.                                  
 * @param serialized_state            Buffer to hold the serialized config blob
 * @param n_serialized_state_max      Maximum available size for the serialized states
 * @param work_buffer                 Work buffer used to parse the blob
 * @param n_work_buffer               Length of the work buffer available for parsing the blob
 * @param n_serialized_state          Actual size of the returned serialized blob
 *
 * @return Zero when successful, otherwise an error code
 */

bsec_library_return_t bsec_get_state(const uint8_t state_set_id, uint8_t * serialized_state,
                const uint32_t n_serialized_state_max, uint8_t * work_buffer, const uint32_t n_work_buffer,
                uint32_t * n_serialized_state);

/**
 * @fn bsec_sensor_control
 * @brief Retrieve BMExxx sensor instructions
 *
 * @n The bsec_sensor_control() interface is a key feature of BSEC, as it allows an easy way for the signal processing 
 * @n library to control the operation of the BME sensor. This is important since gas sensor behaviour is mainly 
 * @n determined by how the integrated heater is configured. To ensure an easy integration of BSEC into any system, 
 * @n bsec_sensor_control() will provide the caller with information about the current sensor configuration that is 
 * @n necessary to fulfill the input requirements derived from the current outputs requested via 
 * @n bsec_update_subscription().
 *
 * @n In practice the use of this function shall be as follows:
 * @n - Call bsec_sensor_control() which returns a bsec_bme_settings_t struct.
 * @n - Based on the information contained in this struct, the sensor is configured and a forced-mode measurement is 
 * @n   triggered if requested by bsec_sensor_control().
 * @n - Once this forced-mode measurement is complete, the signals specified in this struct shall be passed to 
 * @n   bsec_do_steps() to perform the signal processing.
 * @n - After processing, the process should sleep until the bsec_bme_settings_t::next_call timestamp is reached.
 * @param time_stamp                Current timestamp in [ns]
 * @param sensor_settings           Settings to be passed to API to operate sensor at this time instance
 *
 * @return Zero when successful, otherwise an error code
 */

bsec_library_return_t bsec_sensor_control(const int64_t time_stamp, bsec_bme_settings_t *sensor_settings);

#ifdef __cplusplus
 }
#endif

#endif 
