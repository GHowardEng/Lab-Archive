#include "stdafx.h"
#include "CSketch.h"

#define REDVAL Scalar (0, 0, 255)
#define BLUEVAL Scalar (255, 0, 0)
#define GREENVAL Scalar (0, 255, 0)

#define XOFFSET	494
#define YOFFSET 506

CSketch::CSketch(string comport, Size Mat_size)
{
	if (!controller.open(comport))
	{
		exit(0);
	}

	controller.set_data(DIGITAL, _colourState, 1);

	_canvas = Mat::zeros (Mat_size, CV_8UC3);
}

void CSketch::update()
{
	int value;
	int posX;
	int posY;
	
	if (GetTickCount() - time < 50)
	{
		if (controller.get_button(32, 0))
		{
			controller.set_data(DIGITAL, _colourState, 0);
			_colourState++;

			if (_colourState > RED)
			{
				_colourState = BLUE;
			}
			controller.set_data(DIGITAL, _colourState, 1);
		}

		if (controller.get_button(33, 1))
		{
			_reset = 1;
		}
	}
	
	if (GetTickCount() - time > 150)
	{
		time = GetTickCount();
	}
	
	//posX = (controller.get_analog(15, value) * (XSIZE + 15)) / 100;
	//posY = (controller.get_analog(9, value) * (YSIZE + 15)) / 100;

	controller.get_analog(15, value);
	posX = value - XOFFSET;
	
	controller.get_analog(9, value);
	posY = value - YOFFSET;

	LastPoint = NewPoint;
	NewPoint = Point((NewPoint.x + posX*0.04), (NewPoint.y - posY*0.04));
	//NewPoint = Point(posX, YSIZE - posY);

	if (NewPoint.x > XSIZE)
	{
		NewPoint.x = XSIZE;
	}
	else if (NewPoint.x < 0)
	{
		NewPoint.x = 0;
	}

	if (NewPoint.y > YSIZE)
	{
		NewPoint.y = YSIZE;
	}
	else if (NewPoint.y < 0)
	{
		NewPoint.y = 0;
	}
}

void CSketch::draw()
{
	Scalar colour;

	if (_reset)
	{
		_canvas = Mat::zeros(Size(XSIZE, YSIZE), CV_8UC3);
		_reset = 0;
	}

	if (_colourState == RED)
	{
		colour = REDVAL;
	}
	else if (_colourState == GREEN)
	{
		colour =  GREENVAL;
	}
	else if (_colourState == BLUE)
	{
		colour =  BLUEVAL;
	}

	//blur(_canvas, _canvas, Size(3, 3), Point(1, 1));
	line(_canvas, LastPoint, NewPoint, colour, 2);
	
	imshow("Etch-A-Sketch", _canvas);
}

void CSketch::run()
{
	cout << "\nEtch-A-Sketch running, press q to exit\n";
	do
	{
		update();
		draw();
	} while (waitKey(1) != 'q');

	controller.set_data(DIGITAL, _colourState, 0);
}