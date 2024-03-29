// Physics.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "windows.h"
#include "CControl.h"

using namespace cv;
using namespace std;

#define RADIUS 30
#define XSIZE 1000
#define YSIZE 900

bool DoEvents();

int main()
{
	Point2f center (XSIZE/2, YSIZE/4);
	Point2f velocity (0, 0);
	Point2f accel(0, 2500);
	Point2f lastPoint;

	Point input;
	CControl controller;

	string fps;

	int count = 0;

	int value;
	int open = 0;
	char ch;
	srand(GetTickCount());

	getTickFrequency();
	double time = (double)getTickCount();
	double second = (double)getTickCount();

	int runTime = GetTickCount();

	Mat canvas; 

	open = controller.open("COM5");
	canvas = Mat::zeros(Size(XSIZE, YSIZE), CV_8UC3);

	velocity.x = -1000 + rand() % 2000;
	do
	{
		lastPoint = center;

		canvas = Mat::zeros(Size(XSIZE, YSIZE), CV_8UC3);

		time = ((double)getTickCount() - time) / getTickFrequency();

		if (((double)getTickCount() - second) / getTickFrequency() > 1)
		{
			fps = "FPS: " + to_string(count);
			count = 0;
			second = (double)getTickCount();
		}

		velocity += accel * time;
		center += velocity * time;

 		time = (double)getTickCount();

		if (center.x + RADIUS >= XSIZE)
		{
			velocity.x = -0.65 * velocity.x;

			center.x = XSIZE - RADIUS;
		}

		else if (center.x - RADIUS <= 0)
		{
			velocity.x = -0.65 * velocity.x;

			center.x = 0 + RADIUS;
		}

		if (center.y + RADIUS >= YSIZE)
		{
			velocity.y = -0.75 * velocity.y;

			center.y = YSIZE - RADIUS;
		}

		else if (center.y - RADIUS <= 0)
		{
			velocity.y = -0.95 * velocity.y;

			center.y = 0 + RADIUS;
		}
		
		circle(canvas, center, RADIUS, Scalar(255, 255, 255), 4);
		line(canvas, lastPoint, center, Scalar(0, 0, 255), 2);
		cv::putText(canvas, fps, Point(15, 20), 1, 1, Scalar::all(255), 1);
		imshow("PHYSICS!...Kinda", canvas);

		count += 1;

		DoEvents();

		if (open && GetTickCount() % 50 == 0)
			value = controller.get_button(33, 1);
		else
			value = 0;

		if (GetTickCount() - runTime > 15000 || value)
		{
			center = Point2f (XSIZE / 2,  YSIZE / 2);
			
			if (open)
			{
				do
				{
					canvas = Mat::zeros(Size(XSIZE, YSIZE), CV_8UC3);

					input.x = (controller.get_analog(15, value) * XSIZE/100);
					input.y = YSIZE - (controller.get_analog(9, value) * YSIZE/100);

					circle(canvas, center, RADIUS, Scalar(0, 0, 255));
					line(canvas, center, input, Scalar(0, 0, 255));

					velocity = Point2f((center.x - input.x) * 5 , -((input.y - center.y) * 5));

					imshow("PHYSICS!...Kinda", canvas);
					ch = waitKey(1);

					time = (double)getTickCount();

				} while (!controller.get_button(32, 0) && ch != 'q');
			}
			else
			{
				velocity = Point2f((-1500 + rand() % 3000), (-1500 + rand() % 3000));
				time = (double)getTickCount();
			}	
			runTime = GetTickCount();
		}
	} while (1);

    return 0;
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