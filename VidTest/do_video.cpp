////////////////////////////////////////////////////////////////
// Display video on screen using Canny edge detection
////////////////////////////////////////////////////////////////

#include <opencv2/opencv.hpp>

#define ball_area 100000

using namespace std;
using namespace cv;

void do_video();
void blue_vid();


class test
{
public:
	bool in_frame();
	void blue_vid();
	
	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;
	
	Mat frame;

};

int main()
{
	test c;
	
	do
	{
	//do_video();

	if(c.in_frame())
	{
		c.blue_vid();
	}
	
	} while (cv::waitKey(10) != ' ');
	

	
	return 0;
}

void do_video()
{
  cv::VideoCapture vid;
  cv::Mat frame, edges;

  vid.open(0);

  if (vid.isOpened() == true)
  {
    do
    {
  
      vid >> frame;
      if (frame.empty() == false)
      {
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7, 7), 1.5, 1.5);
        cv::Canny(edges, edges, 0, 30, 3);
        cv::imshow("edges", edges);
      }
    }
    while (cv::waitKey(20) != ' ');
  }      
}	


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
		cv::Mat gray, mask;

		vid >> frame;

		if (frame.empty() == false)
		{
			cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
			cv::inRange(gray, 75, 255, mask);

			cv::erode(mask, mask, cv::Mat());
			cv::dilate(mask, mask, cv::Mat());

			findContours(mask, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
			imshow("Frame", frame);
			
			for (int i = 0; i < contours.size(); i++)
			{
				area = contourArea(contours.at(i));
			
				if (area > ball_area)
				{
					//drawContours(mask, contours, i, Scalar::all(255), 5, 8, hierarchy);
					
					//imshow("Object Detection", mask);
					
					return true;
				}
			}
		}
	}

	return false;
	cout << "\nEmpty";
}


void test::blue_vid()
{
	cv::Scalar lower_blue(100, 100, 100);
	cv::Scalar upper_blue(123, 255, 255);

	cv::Scalar lower_red(0, 120, 30);
	cv::Scalar upper_red(8, 255, 245);

	vector<Vec4i> hierarchy;
	vector<vector<Point>> contours;
	vector<Point> contour;
	int area;

	cv::Mat hsv, mask, res;

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

		for (int i = 0; i < contours.size(); i++)
		{
			area = contourArea(contours.at(i));
			
			if (area > ball_area)
			{
				
				drawContours(frame, contours, i, Scalar::all(255), 2, 8, hierarchy);
				
				cv::Rect bound (boundingRect(contours.at(i)));	
				rectangle(frame, bound, Scalar::all(255), 2);
				
				putText(frame, "Pass", Point(20,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 255, 10), 2);		
	
				i = contours.size();
			}
			
		}
			
		if(contours.size() == 0)
		{
			putText(frame, "Reject", Point(20,40), FONT_HERSHEY_DUPLEX, 1, Scalar(20, 10, 255), 2);
		}
			
			
		

		cv::imshow("Result", res);
		cv::imshow("Frame", frame);
		

		
	}
}

