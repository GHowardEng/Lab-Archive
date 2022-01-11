#pragma once
#include "stdafx.h"
#include "CBase4618.h"

#define VINITIAL 400
/**
*
* @brief Uses openCV to play a game of pong.
*
*
* This class inherits from the CBase4618 class and overloads functions to implement the classic 'Pong' game. Requires openCV.
*
*
* @author Grant Howard
*
*/
class CPong : public CBase4618
{
private:
	double _time = (double)getTickCount();
	double start_time = getTickCount();
	double run_time;
	
	double frame_time = getTickCount();
	int count = 0;

	Point velocity;
	Point position;
	int paddle_vel;
	Point paddle_center;
	Point opponent_center;
	int _reset = 0;
	int gameover = 0;

	int VMAX = VINITIAL;

	int player_score = 0;
	int npc_score = 0;
	int ch = 0;

	string frames;

	static void update_thread(CPong* ptr);
	static void draw_thread(CPong* ptr);
	
	bool thread_exit = false;

	Mutex pong;
	
public:
	/** @brief Constructor to initiallize comport and size of canvas.
	*
	* @param comport The desired port to be used ("COMx")
	* @param Mat_size Dimensions of canvas (width, height)
	*
	*
	* @return No return value
	*
	*/
	CPong(string comport, Size Mat_size);

	/** @brief Reads vertical joystick input and updates velocity/positions for the paddles and ball.
	*
	* @return No return value
	*
	*/
	void update();

	/** @brief Uses updated coordinates to draw objects and displays image.
	*
	* @return No return value
	*
	*/
	void draw();

	/** @brief Runs program by calling update() and draw() in detached threads.
	*
	* @return No return value
	*
	*/
	void run();


};