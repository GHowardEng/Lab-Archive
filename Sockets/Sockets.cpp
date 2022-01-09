// Sockets.cpp : Defines the entry point for the console application.
//

#include "server.h"
#include "wiringPi.h"
#include "CBlueSort.hpp"
#include <thread>

#define SYS '0'
#define ON '1'
#define OFF '0'

#define SORT '1'
#define Pass '0'
#define Rej	 '1'

#define cmd 2 
#define val 4

using namespace std;
using namespace cv;

Server serv;
void serverfunc();


// Send image to TCP server
void serverimagefunc();

int main()
{
	std::string rx;
	std::string tx;
	char ch = 0;
	bool status = false;
	int stat = 0;
	int value = 0;
	
	serv._exit = false;

	cv::Mat im;
	
	CBlueSort sort;
	
	// Start server
	std::thread t1(&serverfunc);
	t1.detach();
	
	// Wait until server starts up (webcam is slow)
	delay(2000);

	// Start image send to server
	//std::thread t2(&serverimagefunc);
	//t2.detach();

	// Wait until server starts up (webcam is slow)
	delay(1000);

	cout << "Server Running. Send 'q' from client to exit.\n";
	
	sort.pass_count = 0;
	sort.rej_count = 0;
	
	sort.controller.set_data(SERVO, SM0, CENTER);
	sort.controller.set_data(DIGITAL, STAT_LED, 0);
	
	do
	{
		if (serv.str[0] != 'i' && serv.str[0] != ' ')
			cout << "\n" << serv.str;
		
		if (serv.str.length() > 1)
		{
			
			if (serv.str[0] == 'g' || serv.str[0] == 'G')
			{		
				if (serv.str[cmd] == SYS)
				{
					
					sort.controller.get_data(DIGITAL, STAT_LED, value);

					if (stat == 1)
					{
						serv.reply = "ON";
						send(serv.clientsock, serv.reply.c_str(), serv.reply.length(), 0);
					}
					
					else 
					{
						serv.reply = "OFF";
						send(serv.clientsock, serv.reply.c_str(), serv.reply.length(), 0);
					}
					
					
				}
				
				else if (serv.str[cmd] == SORT)
				{
					serv.reply = to_string(sort.pass_count) + " / " + to_string(sort.rej_count);
					send(serv.clientsock, serv.reply.c_str(), serv.reply.length(), 0);
				}
					
				serv.str = " n";
				
			}
			else if(serv.str[0] == 's' || serv.str[0] == 'S')
			{
						
				if (serv.str[cmd] == SYS)
				{

					if (serv.str[val] == ON)
					{
						status = true;
						stat = 1;
					}
					
					else if (serv.str[val] == OFF)
					{
						status = false;
						stat = 0;
					}
					
					serv.str = " n";
					
					
				}
				
				
				
				else if (serv.str[cmd] == SORT)
				{
					if (serv.str[val] == Pass)
					{
						sort.pass();
					}
					
					else if (serv.str[val] == Rej)
					{
						sort.reject();
					}
					
					serv.str = " n";
					
					
				}
			}
			
			
		}
		
		sort.get_frame();
	

		if(status)
		{
			
			sort.controller.set_data(DIGITAL, STAT_LED, 1);
		}
		
		else
		{
			
			sort.controller.set_data(DIGITAL, STAT_LED, 0);
		}
		
		
		if (status)
		{
				
			if (sort.in_frame())
			{
				
				if (sort.blue_vid() || (status == 0 && sort.result == 'p'))
				{
					sort.pass();
				}
				
				else 
				{
					sort.reject();
				}
			}
		}
				
		
		else if (sort.result == 'p' || sort.controller.get_button(PASS_BUTTON, 1))
			sort.pass();
			
		else if (sort.result == 'r' || sort.controller.get_button(REJ, 2))
			sort.reject();
					
		serv.set_txim(sort.frame);
			
	//	cin >> ch;

	} while (serv.str[0] != 'q');

	serv._exit = true;
    return 0;
}


// Start TCP server
void serverfunc()
{
	serv.start(4618);
}

// Send image to TCP server
void serverimagefunc()
{
	cv::VideoCapture vid;

	vid.open(0);

	if (vid.isOpened() == TRUE)
	{
		do
		{
			cv::Mat frame;
			vid >> frame;
			serv.set_txim(frame);
		} while (serv._exit != true);
	}
}

