
#include "CControlPi.hpp"
#include "pigpio.h"
#include "wiringPi.h"

#include <iostream>

using namespace std;


void CControlPi::open(string com)
{
	
}

CControlPi::CControlPi()
{
	gpioInitialise();
	
	gpioSetMode(B0, PI_INPUT);
	gpioSetMode(LED, PI_OUTPUT);
	gpioSetMode(SM0, PI_OUTPUT);
		
}
bool CControlPi::get_data(int type, int channel, int &value)
{
	if (type == DIGITAL)
	{
		value = gpioRead (channel);
		return true;
	}
	
	else if (type == ANALOG)
	{
		unsigned char inBuf[3];
		char cmd[] = { 1, 128, 0 };
		
		int handle = spiOpen(channel, 200000, 3);
		
		spiXfer(handle, cmd, (char*) inBuf, 3);
		value = ((inBuf[1] & 3) << 8) | inBuf[2];
		
		spiClose(handle);
		
		return true;
	}
	return false;
}

bool CControlPi::set_data(int type, int channel, int value)
{
	if (type == DIGITAL)
	{
		gpioWrite(channel, value);
		return true;
	}
	
	else if (type == SERVO)
	{
		gpioServo(channel, value);
		return true;
	}
	
	return false;
}

int CControlPi::get_analog(int channel, int &value)
{
	if (get_data(ANALOG, channel, value))
	{
		return (100 * (value)) / 1023;
	}

}

int CControlPi::get_button(int channel, int index)
{
	int value;
	get_data(DIGITAL, channel, value);

	if (value != lastval[index])
	{
		lastval[index] = value;
		delay(2);
		
		get_data(DIGITAL, channel, value);
		if (value == 0)
		{
			return 1;
		}
	}
	

	return 0;
}

void CControlPi::print_menu(void)
{

	cout << "\n\n******************************";
	cout << "\n\n(B)utton Count";
	cout << "\n(D)igital Input/Output";
	cout << "\n(A)nalog Inputs";
	cout << "\n(S)ervo Test";
	cout << "\n(C)ontrol Servo";
	cout << "\n(Q)uit";
	cout << "\n\nCommand> ";

}
