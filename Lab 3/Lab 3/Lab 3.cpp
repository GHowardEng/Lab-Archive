// ELEX Lab 3 - Serial Communication and Control of an Embbeded System
// Grant Howard, A00970152
// January 27th, 2018

#include "stdafx.h"

#define MAX 250
#define MIN 0

#define JSX 15
#define JSY 9

int main()
{
	CControl ser_control;
	string com_port;

	int value = 1;
	int value2 = 0;
	int lastval = 1;
	int per1;
	int per2;
	char cmd;
	int count = 0;
	int time;

	cout << "\n\n*********************************************";
	cout << "\nMSP432 Serial Control System by Grant Howard";
	cout << "\n*********************************************\n\n";

	do		// Get COM port from user and attempt to open
	{
		cout << "Select communication port (COMx): ";
		cin >> com_port;

		
	} while (!(ser_control.open(com_port)));	// Repeat if connection unsuccessful

	while (1)
	{
		ser_control.print_menu();
		cin >> cmd;

		if (cmd == 'd' || cmd == 'D')
		{
			ser_control.get_data(DIGITAL, 32, value);		// Read push button 
			ser_control.set_data(DIGITAL, 38, value);		// Write value to Red and Green LED's (Yellow)
			ser_control.set_data(DIGITAL, 39, value);
			cout << "\n\nDIGITAL TEST: CH 32 = " << value;

			time = GetTickCount();		
			while (GetTickCount() - time < 10000)
			{
				if (GetTickCount() % 5 == 0)		// Run every five milliseconds
				{
					lastval = value;
					if (ser_control.get_data(DIGITAL, 32, value))
					{
						if (lastval != value)	// If transition detected
						{
							cout << "\n\nDIGITAL TEST: CH 32 = " << value;	// Print value and write to LED's
							ser_control.set_data(DIGITAL, 38, value);
							ser_control.set_data(DIGITAL, 39, value);
						}
					}

					else
					{
						cout << "\n\nNo Connection";
					}
				}
			}
		}

		else if (cmd == 's' || cmd == 'S')
		{
			time = GetTickCount();
			while (GetTickCount() - time < 5000)	// Cycle servo for 5 seconds
			{
				ser_control.set_data(SERVO, 0, MAX);	// Set to maximum position

				Sleep(600);		// Allow servo to rotate

				if (ser_control.get_data(SERVO, 0, value))
				{
					cout << "\n\nSERVO TEST: CH 0 = " << value;		// Get servo position
				}

				ser_control.set_data(SERVO, 0, MIN);		// Set to minimum position

				Sleep(600);

				if (ser_control.get_data(SERVO, 0, value))
				{
					cout << "\n\nSERVO TEST: CH 0 = " << value;
				}

				else
				{
					cout << "\n\nNo Connection";
				}
			}
		}

		else if (cmd == 'a' || cmd == 'A')
		{
			time = GetTickCount();
			while (GetTickCount() - time < 20000)
			{
				if (GetTickCount() % 6 == 0)
				{
					per1 = ser_control.get_analog(JSX, value);		// Read joystick X position

					per2 = ser_control.get_analog(JSY, value2);		// Read joystick Y position
					
					ser_control.set_data(ANALOG, 39, (per1 * 255) / 100);
					// Print results 
					cout << "\n\nANALOG TEST: CH 9 = " << value << " (" << per1 << "%), " << "CH 15 = " << value2 << " (" << per2 << "%)";
				}
			}
		}

		else if (cmd == 'b' || cmd == 'B')
		{
			cout << "\n\nBUTTON TEST: " << count;
			
			time = GetTickCount();
			while (GetTickCount() - time < 20000)
			{
				if (ser_control.get_button(32))
				{
					count += 1;
					cout << "\n\nBUTTON TEST: " << count;
				}
			}
		}

		else if (cmd == 'c' || cmd == 'C')
		{
			cout << "\nSet servo position";

			time = GetTickCount();
			while (GetTickCount() - time < 20000)
			{
				cout << "\n\nPosition in degrees: ";
				cin >> value;

				if (ser_control.set_data(SERVO, 0, value))
				{
					cout << "\nRX: " << ser_control.s_rx_str;
				}

				else
				{
					cout << "\nNo Connection\n";
				}
			}
		}

		else if (cmd == 'q' || cmd == 'Q')
		{
			exit(0);
		}
	}

    return 0;
}

