#pragma once

#include "CBase4618.hpp"
#define ball_area 65000

#include "wiringPi.h"

#include <opencv2/opencv.hpp>

#include "raspicam_cv.h"

#include <thread>

using namespace std;
using namespace cv;

class CBlueSort : public CBase4618
{
public:
	CBlueSort();
	~CBlueSort();
	bool in_frame();
	bool blue_vid();
	void get_frame();
	
	void pass();
	void reject();
	
	void update();
	void draw();
	void run();
	
	raspicam::RaspiCam_Cv Camera;
	
	int result = 0; 

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;
	
	Mat frame;

	int pass_count = 0;
	int rej_count = 0;

};
