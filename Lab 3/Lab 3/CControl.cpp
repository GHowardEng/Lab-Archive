
#include "stdafx.h"
#include "CControl.h"

using namespace std;

bool CControl::open(string com_port)
{
	int data;
	s_port.open(com_port);

	Sleep(1);

	if (get_data(DIGITAL, 32, data))
	{
		cout << "Connected\n";
		return true;
	}
	else
	{
		cout << "\nCould not open communications with MSP on selected port\n\n";
		return false;
	}
}

bool CControl::get_data(int type, int channel, int &value)
{
	string val_str;
	char buff[2];

	tx_str = "G " + to_string(type) + " " + to_string(channel);
	s_port.write(tx_str.c_str(), tx_str.length());

	Sleep(2);

	rx_str = "";
	// start timeout count
	float start_time = GetTickCount();

	buff[0] = 0;
	// If 1 byte was read then print to screen, timeout after 1 second
	while (buff[0] != '\n' && GetTickCount() - start_time < 1000)
	{
		if (s_port.read(buff, 1) > 0)
		{
			rx_str = rx_str + buff[0];
		}
	}

	//cv::waitKey(1);	

	s_port.flush();

	if (rx_str[0] == 'A' && rx_str[1] == ' ' && rx_str.find_first_of("0123456789") == 2)
	{
		val_str = rx_str.substr(6, (rx_str.size() - 1));
		value = stoi(val_str);

		return true;
	}
	else
	{
		return false;
	}
}

bool CControl::set_data(int type, int channel, int value)
{
	char buff[2];

	tx_str = "S " + to_string(type) + " " + to_string(channel) + " " + to_string(value);
	s_port.write(tx_str.c_str(), tx_str.length());

	Sleep(2);

	s_rx_str = "";
	// start timeout count
	float start_time = GetTickCount();

	buff[0] = 0;
	// If 1 byte was read then print to screen, timeout after 1 second
	while (buff[0] != '\n' && GetTickCount() - start_time < 1000)
	{
		if (s_port.read(buff, 1) > 0)
		{
			s_rx_str = s_rx_str + buff[0];
		}
	}
	//cv::waitKey(1);

	s_port.flush();

	if (s_rx_str[0] == 'A' && s_rx_str[1] == ' ' && s_rx_str.find_first_of("0123456789") == 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int CControl::get_analog(int channel, int &value)
{
	if (get_data(ANALOG, channel, value))
	{
		return (100 * value) / 1023;
	}
}

int CControl::get_button(int channel)
{
	int value = 1;
	
	float time = GetTickCount();

	while (time - GetTickCount() < 1000)
	{
		if (GetTickCount() % 2 == 0)
		{
			get_data(DIGITAL, channel, value);
			if (value != lastval)
			{
				lastval = value;
				Sleep(5);
				if (value == 0)
				{
					get_data(DIGITAL, channel, value);

					if (value == 0)
					{
						return 1;
					}
				}
			}
		}
	}
	return 0;
}

void CControl::print_menu(void)
{
	Sleep(1);

	set_data(SERVO, 0, 0);
	set_data(DIGITAL, 38, 0);
	set_data(DIGITAL, 39, 0);

	cout << "\n\n******************************";
	cout << "\n\n(B)utton Count";
	cout << "\n(D)igital Input/Output";
	cout << "\n(A)nalog Inputs";
	cout << "\n(S)ervo Test";
	cout << "\n(C)ontrol Servo";
	cout << "\n(Q)uit";
	cout << "\n\nCommand> ";

}