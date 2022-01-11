#pragma once

#include "stdafx.h"


/** @brief Enum for data types used by get_data and set_data
*
*/
enum TYPE { DIGITAL = 0, ANALOG, SERVO };

/**
*
* @brief Provides functionality for the control of a remote microcontroller system.
*
*
* This class is meant to provide functions to interact with inputs and outputs on a remote microcontroller device 
* via serial communictations.
*
*
* @author Grant Howard
*
*/
class CControl
{
private:
	Serial s_port; ///< Serial port object to read/write buffer

	std::string tx_str;	///< Data string to be transmitted

	int lastval[5];  ///< Stores previous button state for de-bouncing

public:
	std::string rx_str;	///< Data string recieved from get operations
	std::string s_rx_str; ///< Data string recieved from set operations
	float time;

	/** @brief Opens communications on selected port.
	*
	* @param com_port The desired port to be used (COMx)
	* @return No return value
	*
	*/
	bool open(std::string com_port);

	/** @brief Retrieves data of given type on selected channel.
	*
	* @param type The data type to be retrieved (DIGITAL, ANALOG, SERVO)
	* @param channel The input channel to be tested
	* @param &value The memory location to store the resulting data
	*
	* @return Returns true if operation succeeded, otherwise returns false
	*/

	void print_menu(void);

	bool get_data(int type, int channel, int &value);

	/** @brief Writes data of given type on selected channel.
	*
	* @param type The data type to be set (DIGITAL, ANALOG, SERVO)
	* @param channel The input channel to be written to
	* @param value The data to be written
	*
	* @return Returns true if operation succeeded, otherwise returns false
	*/
	bool set_data(int type, int channel, int value);

	/** @brief Retrieves ADC conversion of selected analog input.
	*
	* @param channel The analog input channel to be tested (1 for 'A1' etc.)
	* @param &value The memory location to store the conversion result
	* 
	* @return Returns the result as a percentage of full scale
	*/
	int get_analog(int channel, int &value);

	/** @brief De-bounces digital input on selected channel. Uses 1 second timeout.
	*
	* @param channel The digital input channel to be de-bounced
	*
	* @return Returns 1 if negative transition detected (active low button), returns 0 after timeout
	*/
	int get_button(int channel, int index);
};
