#include "CControlPi.hpp"
#include <iostream>
#include "pigpio.h"
#include "wiringPi.h"
#include <opencv2/opencv.hpp>
 
using namespace cv;

using namespace std;


int main()
{
	CControlPi ctrl;
	
	int last;
	int value = 1;
	char cmd;
	int count;
	int per;
	
	cout << "\n\n***************************************************";
	cout << "\nRaspberry Pi GPIO Control System by Grant Howard";
	cout << "\n***************************************************\n\n";
	

	do
	{
		ctrl.print_menu();
		cin >> cmd;
				
		if (cmd == 'd' || cmd == 'D')
		{
			count = 0;
			
			ctrl.get_data(DIGITAL, B0, value);		// Read push button 
			ctrl.set_data(DIGITAL, LED, value);		// Write value to LED
			cout << "Digital Test: " << value << "\n";
		
			while(count < 15)
			{
				last = value;
					
				if (ctrl.get_data(DIGITAL, B0, value))
				{
					if (last != value)	// If transition detected
					{
						cout << "Digital Test: " << value << "\n";
						ctrl.set_data(DIGITAL, LED, value);
						count += 1;
					}
				}
				delay(1);
			}
			ctrl.set_data(DIGITAL, LED, 0);
		}
		
		else if (cmd == 'a' || cmd == 'A')
		{
			count = 0;
			while(count < 7500)
			{
				per = ctrl.get_analog(0, value);
				cout << "Analog Test: " << value << " (" << per << "%)" << "\n";
				delay(2);
				count += 1;
			}
		}
		
		else if (cmd == 's' || cmd == 'S')
		{
			count = 0;
			cout << "\nServo Test\n\nPulse Width (us);\n";
			
			while (count < 5)
			{
				ctrl.set_data(SERVO, SM0, SERVO_MAX);
				cout << SERVO_MAX << "\n";
				delay(800);
				
				ctrl.set_data(SERVO, SM0, SERVO_MIN); 
				cout << SERVO_MIN << "\n";
				delay(800);
				
				count += 1;
			}
		}
		
		else if (cmd == 'c' || cmd == 'C')
		{
			cout << "Set servo to position: ";
			cin >> value;
			
			ctrl.set_data(SERVO, SM0, value);
		}
		
		else if (cmd == 'b' || cmd == 'B')
		{
			count = 0;
			cout << "\n\nBUTTON TEST\nCount: \n";
			cout << count << "\n";
			
			while (count < 10)
			{
				if (ctrl.get_button(B0, 0))
				{
					count += 1;
					cout << count << "\n";
				}
			}
		}
		
		
		
	}while(cmd != 'q' && cmd != 'Q');
	
	gpioTerminate();
	return 0;
}
