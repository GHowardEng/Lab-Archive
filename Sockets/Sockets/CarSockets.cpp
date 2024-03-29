// Sockets.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "Client.h"
#include "server.h"
#include "conio.h"
#include "windows.h"

using namespace std;
using namespace cv;

Server serv;
void serverfunc();

// connect
//Client client(4618, "127.0.0.1");		// Local address (This PC)
//Client client(4618, "192.168.1.72");	// Address on home network
//Client client(4618, "192.168.1.70");	// Address on home network
//Client client(4618, "192.168.137.60");	// Address on Surface hotspot
Client client(4618, "192.168.1.3");	


bool thread_exit = false;
bool thread_pause = false;

// Send image to TCP server
void serverimagefunc();

// Request image from Server and display
void disp_image();

// Function to bypass cv::waitkey() (no frame-rate limit)
bool DoEvents();

int main()
{
	std::string rx;
	std::string tx;
	int count = 0;
	char ch = 0;

	// Start server (for testing locally)
	//std::thread t1(&serverfunc);
	//t1.detach();

	// Start image display
	std::thread t2(&disp_image);
	t2.detach();
	
	// Wait until server starts up (webcam is slow)
	Sleep(1000);
	thread_pause = true;

	/*
	do
	{
		client.tx_str("m");
		cout << "\nConnecting...\n";
		Sleep(1200);
		client.rx_str(rx);
		
	} while (rx != "AUTO MODE");

	do
	{
		client.tx_str("m");
		Sleep(1200);
		client.rx_str(rx);

	} while (rx != "MANUAL MODE");*/

	cout << "Send 'q' to shutdown server and exit.\n";
	thread_pause = false;

	do
	{
		cout << "\n\ncmd> ";
		///std::getline(std::cin, tx);
		tx = _getche();

		thread_pause = true;
		Sleep(350);			// Pause Image Request and wait for buffer to clear

		client.tx_str(tx);

		if (tx[0] == 'm')
		{
			Sleep(500);

			client.rx_str(rx);

			cout << "\n" << rx;
		}
		
		//disp_image();
		thread_pause = false;

	} while (tx[0] != '`');

	client.tx_str("`");
	thread_exit = true;
	Sleep(1000);
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
		} while (cv::waitKey(10) != ' ');
	}
}

void disp_image()
{
	cv::Mat im;

	do
	{
		while(thread_pause == true)
		{ }

		Sleep(40);
		client.tx_str("im");

		if (client.rx_im(im) == TRUE)
		{
			if (im.empty() == false)
			{
				cv::imshow("Car Image", im);
				//cv::waitKey(1);
				DoEvents();
			}
		}
	} while (thread_exit != true);
}

bool DoEvents()
{
	MSG msg;
	BOOL result;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
	{
		result = ::GetMessage(&msg, NULL, 0, 0);
		if (result == 0) // WM_QUIT
		{
			::PostQuitMessage(msg.wParam);
			return false;
		}
		else if (result == -1)
			return true;    //error occured
		else
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}

	return true;
}