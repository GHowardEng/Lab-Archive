////////////////////////////////////////////////////////////////
// ELEX 4618 Template project for BCIT
// Created Oct 5, 2016 by Craig Hennessey
// Last updated March 23, 2017
////////////////////////////////////////////////////////////////
#include "stdafx.h"

#include <string>
#include <iostream>
#include <thread>

#include "Client.h"
#include "Server.h"
#include "Serial.h" // Must include Windows.h after Winsock2.h, so Serial must include after Client/Server

// OpenCV Include
#include "opencv.hpp"

// OpenCV Library
#pragma comment(lib,".\\opencv\\lib\\opencv_world310d.lib")

#define ball_area 20000

using namespace std;
using namespace cv;

////////////////////////////////////////////////////////////////
// Serial Communication
////////////////////////////////////////////////////////////////
void test_com()
{
  // Comport class
  Serial com;
  com.open("COM51");

  // TX and RX strings
  std::string tx_str = "G 1 1\n";
  std::string rx_str;

  // temporary storage
  char buff[2];
  do
  {
    // Send TX string
		com.write(tx_str.c_str(), tx_str.length());
    Sleep(10); // not needed?
  
    rx_str = "";
    // start timeout count
    float start_time = GetTickCount();

    buff[0] = 0;
		// If 1 byte was read then print to screen, timeout after 1 second
    while (buff[0] != '\n' && GetTickCount() - start_time < 1000)
    {
      if (com.read(buff, 1) > 0)
      {
        rx_str = rx_str + buff[0];
      }
    }

    printf ("\nRX: %s", rx_str.c_str());
    cv::waitKey(1);
  } 
  while (1);
}

////////////////////////////////////////////////////////////////
// Display Image on screen
////////////////////////////////////////////////////////////////
void do_image()
{
  cv::Mat im;

  im = cv::imread("BCIT.jpg");

  srand(time(0));

  for (int i = 0; i < 500; i++)
  {
    float radius = 50 * rand() / RAND_MAX;
    cv::Point center = cv::Point(im.size().width*rand() / RAND_MAX, im.size().height*rand() / RAND_MAX);
    
    cv::circle(im, center, radius, cv::Scalar(200, 200, 200), 1, cv::LINE_AA);
    
    im.at<char>(i,i) = 255;
    
    cv::imshow("Image", im);
    cv::waitKey(1);
  }
}

////////////////////////////////////////////////////////////////
// Display Video on screen
////////////////////////////////////////////////////////////////
void do_video()
{
  cv::VideoCapture vid;

  vid.open(0);

  if (vid.isOpened() == TRUE)
  {
    do
    {
      cv::Mat frame, edges;
      vid >> frame;
      if (frame.empty() == false)
      {
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
      }
    }
    while (cv::waitKey(10) != ' ');
  }      
}	

void blue_vid()
{
	cv::VideoCapture vid;

	cv::Scalar lower_blue(100, 100, 50);
	cv::Scalar upper_blue(123, 255, 255);

	cv::Scalar lower_red(0, 120, 30);
	cv::Scalar upper_red(8, 255, 245);

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;
	int area;

	vid.open(0);

	if (vid.isOpened())
	{
		do
		{
			cv::Mat frame, hsv, mask, res;

			vid >> frame;

			if (frame.empty() == false)
			{
				cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
				cv::inRange(hsv, lower_blue, upper_blue, mask);
				//cv::inRange(hsv, lower_red, upper_red, mask);

				cv::erode(mask, mask, cv::Mat());
				cv::dilate(mask, mask, cv::Mat());
			
				findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

				for (int i = 0; i < contours.size(); i++)
				{
					drawContours(mask, contours, i, Scalar::all(255), CV_FILLED, 8, hierarchy);
				}
				
				cv::bitwise_and(frame, frame, res, mask);

				for (int i = 0; i < contours.size(); i++)
				{
					drawContours(res, contours, i, Scalar (0, 20, 255), 2, 8, hierarchy);
					area = contourArea(contours.at(i));
				}
	
				cv::imshow("Result", res);
			//	cv::imshow("Frame", frame);
			}

		} while (cv::waitKey(10) != ' ');
	}
}
    

////////////////////////////////////////////////////////////////
// Demo client server communication
////////////////////////////////////////////////////////////////
Server serv;

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
    }
    while (cv::waitKey(10) != ' ');
  }
}

void clientserver()
{
  std::string str;
  cv::Mat im;

  // Start server
  std::thread t1(&serverfunc);
  t1.detach();

  // Start image send to server
  std::thread t2(&serverimagefunc);
  t2.detach();

  // Wait until server starts up (webcam is slow)
  Sleep(2000);

  // connect
  Client client(4618, "127.0.0.1");
  //Client client(4618, "192.168.1.80");

  // Wait until server starts up (webcam is slow)
  Sleep(500);

  client.tx_str("cmd");
  do
  {
    client.rx_str(str);
    if (str.length() > 0)
    {
      std::cout << "\nClient Rx: " << str;
    }
  } while (str.length() == 0);

  int count = 0;
  while (1)
  {
    client.tx_str("im");

    if (client.rx_im(im) == TRUE)
    {
      if (im.empty() == false)
      {
        count++;
        std::cout << "\nImage received: " << count;
        cv::imshow("rx", im);
        cv::waitKey(100);
      }
    }
  }
}

class test
{
public:
	bool in_frame();

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;

};
bool test::in_frame()
{
	cv::VideoCapture vid;

	cv::Scalar lower_blue(100, 100, 50);
	cv::Scalar upper_blue(123, 255, 255);

	cv::Scalar lower_red(0, 120, 30);
	cv::Scalar upper_red(8, 255, 245);


	int area;

	vid.open(0);

	if (vid.isOpened() == true)
	{
		cv::Mat frame, gray, mask;

		vid >> frame;

		if (frame.empty() == false)
		{
			cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
			cv::inRange(gray, 60, 255, mask);

			cv::erode(mask, mask, cv::Mat());
			cv::dilate(mask, mask, cv::Mat());

			findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			
			for (int i = 0; i < contours.size(); i++)
			{
				drawContours(mask, contours, i, Scalar::all(255), 3);//, 8, hierarchy);
		
				area = contourArea(contours.at(i));

				if (area > ball_area)
				{
					cout << "\n" << area;
					imshow("mask", mask);
					cout << "\n" << area;
					
					return true;
				}
			}
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	test c;
	//test_com();
	//do_image();
	//do_video ();

	/*do
	{
		if (c.in_frame() == true)
		{
			blue_vid();
		}
	//	Sleep(1);
	} while (waitKey(15) != ' ');*/

	  clientserver();

		return 0;
}

