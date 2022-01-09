#include "CBlueSort.hpp"

#define CENTER 	1315
#define PASS	1500
#define REJECT	1100

CBlueSort::CBlueSort()
{
	Camera.open();
}

CBlueSort::~CBlueSort()
{
	Camera.release();
}

void CBlueSort::get_frame()
{
	Camera.grab();
	Camera.retrieve ( frame );
}

bool CBlueSort::in_frame()
{

	int area;

		cv::Mat gray, g_mask;
		contours.clear();
	

		if (frame.empty() == false)
		{
			cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
			cv::inRange(gray, 60, 255, g_mask);

			cv::erode(g_mask, g_mask, cv::Mat());
			cv::dilate(g_mask, g_mask, cv::Mat());

			findContours(g_mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			
			for (int i = 0; i < contours.size(); i++)
			{
				area = contourArea(contours.at(i));
			
				if (area > ball_area)
				{
					//drawContours(frame, contours, i, Scalar (10, 10, 250), 4, 8, hierarchy);
					
					//cv::Rect bound (boundingRect(contours.at(i)));	
					//rectangle(frame, bound, Scalar (10, 10, 250), 1);
					
					//imshow("Object Detection", g_mask);
					
					return true;
				}
			}
		}
	

	return false;
}


bool CBlueSort::blue_vid()
{
	cv::Scalar lower_blue(100, 130, 180);
	cv::Scalar upper_blue(123, 255, 255);
	
	cv::Mat hsv, mask, res;

	contours.clear();
	
	int area;


	if (frame.empty() == false)
	{
		cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);
		cv::inRange(hsv, lower_blue, upper_blue, mask);

		cv::erode(mask, mask, cv::Mat());
		cv::dilate(mask, mask, cv::Mat());
	
		findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

		for (int i = 0; i < contours.size(); i++)
		{
			drawContours(mask, contours, i, Scalar::all(255), CV_FILLED, 8, hierarchy);
		}
		cv::bitwise_and(frame, frame, res, mask);
		
		cv::imshow("Result", res);

		for (int i = 0; i < contours.size(); i++)
		{
			area = contourArea(contours.at(i));
			
			if (area > ball_area)
			{
				
				drawContours(frame, contours, i, Scalar::all(255), 2, 8, hierarchy);
				
				cv::Rect bound (boundingRect(contours.at(i)));	
				rectangle(frame, bound, Scalar::all(255), 2);
					
				i = contours.size();
				
				return true;
			}
			
		}
		
		return false;
		
	}
}
int status = 0;



void CBlueSort::update()
{
	
	
	//get_frame();
	
	if (result == 's' || controller.get_button(STAT, 0))
	{
		if(status)
		{
			status = 0;
			controller.set_data(DIGITAL, STAT_LED, 0);
		}
		
		else
		{
			status = 1;
			controller.set_data(DIGITAL, STAT_LED, 1);
		}
	}
	
	if (status)
	{
		
		
		if (in_frame())
		{
			
			if (blue_vid() || (status == 0 && result == 'p'))
			{
				pass();
			}
			
			else 
			{
				reject();
			}
		}
	}
	
	else if (result == 'p' || controller.get_button(PASS_BUTTON, 1))
		pass();
		
	else if (result == 'r' || controller.get_button(REJ, 2))
		reject();
}

void CBlueSort::draw()
{

	putText(frame, to_string(pass_count), Point(140,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 255, 10), 2);
	putText(frame, "/", Point(180,40), FONT_HERSHEY_DUPLEX, 1, Scalar(255, 255, 255), 2);
	putText(frame, to_string(rej_count), Point(220,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 10, 255), 2);
	
	if (status)
	{
		putText(frame, "Status: ON", Point(20, 80), FONT_HERSHEY_DUPLEX, 0.7, Scalar (20, 255, 10), 1);
	}
	
	else
	{
		putText(frame, "Status: OFF", Point(20, 80), FONT_HERSHEY_DUPLEX, 0.7, Scalar (20, 10, 255), 1);
	}
	
	
	cv::imshow("Frame", frame);
}

void CBlueSort::run()
{
	pass_count = 0;
	rej_count = 0;
	
	controller.set_data(SERVO, SM0, CENTER);
	controller.set_data(DIGITAL, STAT_LED, 0);
	
	do
	{
		update();
		draw();
		
		result = waitKey(10);
		
	} while (result != ' ');
}

void CBlueSort::pass()
{
	controller.set_data(DIGITAL, P_LED, 1);
	
	controller.set_data(SERVO, SM0, PASS);
	delay(100);
	controller.set_data(SERVO, SM0, CENTER);
	
	controller.set_data(DIGITAL, P_LED, 0);
	
	putText(frame, "Pass", Point(20,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 255, 10), 2);
	pass_count++;	
}

void CBlueSort::reject()
{
	controller.set_data(DIGITAL, R_LED, 1);
	
	controller.set_data(SERVO, SM0, REJECT);
	delay(100);
	controller.set_data(SERVO, SM0, CENTER);
	
	controller.set_data(DIGITAL, R_LED, 0);
	
	putText(frame, "Reject", Point(20,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 10, 255), 2);
	rej_count += 1;
}
