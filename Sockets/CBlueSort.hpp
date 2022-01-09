#pragma once

#include "CBase4618.hpp"
#define ball_area 65000
#define CENTER 	1315
#define PASS	1500
#define REJECT	1100

#include "wiringPi.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include <opencv2/opencv.hpp>

#include "raspicam_cv.h"

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
