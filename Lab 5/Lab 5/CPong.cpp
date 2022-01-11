#include "stdafx.h"
#include "CPong.h"
#include <math.h>

#define XOFFSET	494
#define YOFFSET 506

#define PADHEIGHT	150
#define PADWIDTH	10

#define RADIUS 20

CPong::CPong(string comport, Size Mat_size)
{
	if (!controller.open(comport))
	{
		//exit(0);
	}

	_canvas = Mat::zeros(Mat_size, CV_8UC3);
	
	velocity = Point (-VMAX, 0);

	position = Point (XSIZE / 2, YSIZE / 2);

	paddle_center = Point(30, YSIZE / 2);
	opponent_center = Point(XSIZE - 30, YSIZE / 2);
	
}



// Run update and draw in standalone threads, wait for exit
void CPong::run()
{
	char ch;

	thread t1(&CPong::update_thread, this);
	t1.detach();

	thread t2(&CPong::draw_thread, this);
	t2.detach();

	do
	{
		cin >> ch;
	} while (ch != 'q');

	thread_exit = true;
}

void CPong::update()
{
	int value;
	int posY;
	int math;

	// Calculate elapsed time
	_time = ((double)getTickCount() - _time) / getTickFrequency();

	// Calculate position based on velocity vector and time passed
	pong.lock();
	position += velocity * _time;
	pong.unlock();

	// Read joystick to set paddle velocity
	controller.get_analog(9, value);
	posY = value - YOFFSET;

	paddle_vel = -3*posY ;

	pong.lock();

	// Set new paddle position
	paddle_center = Point(paddle_center.x, paddle_center.y + (paddle_vel * _time));
	
	// Update time
	_time = getTickCount();

	// Test for ball passing paddle, increment respective score
	if (position.x - RADIUS < paddle_center.x)
	{
		_reset = 1;
		npc_score += 1;
		VMAX = VINITIAL;
	}
	else if (position.x + RADIUS > opponent_center.x)
	{
		_reset = 1;
		player_score += 1;
		VMAX = VINITIAL;
	}

	// Reset scores and set gameover flag
	if (player_score == 5 || npc_score == 5)
	{
		gameover = 1;
		_reset = 1;
		npc_score = 0;
		player_score = 0;
	}

	// Limit paddle movement
	if (paddle_center.y + PADHEIGHT / 2 > YSIZE)
	{
		paddle_center.y = YSIZE - PADHEIGHT / 2;
	}
	else if (paddle_center.y - PADHEIGHT / 2 < 0)
	{
		paddle_center.y = 0 + PADHEIGHT / 2;
	}


	// NPC paddle will track ball y position
	opponent_center.y = position.y;

	if (opponent_center.y + PADHEIGHT / 2 > YSIZE)
	{
		opponent_center.y = YSIZE - PADHEIGHT / 2;
	}
	else if (opponent_center.y - PADHEIGHT / 2 < 0)
	{
		opponent_center.y = 0 + PADHEIGHT / 2;
	}
	pong.unlock();

	run_time = (getTickCount() - start_time) / getTickFrequency();

	// Increase max velocity every 15 seconds
	if (run_time > 20)
	{
		VMAX += 200;
		start_time = getTickCount();
	}

	// Test for collision with player paddle
	if (position.x - RADIUS < paddle_center.x + PADWIDTH / 2 && position.y - RADIUS < (paddle_center.y + PADHEIGHT/2) && position.y + RADIUS > (paddle_center.y - PADHEIGHT/2))
	{
		pong.lock();
		position.x = paddle_center.x + PADWIDTH / 2 + RADIUS;
		pong.unlock();

		// Vertical velocity dependent on paddle velocity
		velocity.y += paddle_vel * 0.25;
		
		if (velocity.y > VMAX - 50)
		{
			velocity.y = VMAX - 50;
		}
		else if (velocity.y < -(VMAX - 50))
		{
			velocity.y = -(VMAX - 50);
		}

		// Calculate x component based on y component
		math = pow(VMAX, 2) - pow(abs(velocity.y), 2);
		velocity.x = sqrt(math);
	}
	// Test for collision with npc paddle
	else if (position.x + RADIUS > opponent_center.x - PADWIDTH / 2 && position.y + RADIUS < opponent_center.y + PADHEIGHT && position.y - RADIUS > opponent_center.y - PADHEIGHT)
	{
		pong.lock();
		position.x = opponent_center.x - PADWIDTH / 2 - RADIUS;
		pong.unlock();
		
		math = pow(VMAX, 2) - pow(abs(velocity.y), 2);
		velocity.x = -sqrt(math);
	}

	// Collision with top or bottom
	if (position.y + RADIUS > YSIZE)
	{
		pong.lock();
		position.y = YSIZE - RADIUS;
		pong.unlock();

		velocity.y = -velocity.y;
	}
	else if (position.y - RADIUS < 0)
	{
		pong.lock();
		position.y = 0 + RADIUS;
		pong.unlock();

		velocity.y = -velocity.y;
	}

	// Reset button
	if (controller.get_button(33, 0))
	{
		pong.lock();
		_reset = 1;
		npc_score = 0;
		player_score = 0;
		pong.unlock();
		start_time = getTickCount();

		run_time = 0;
		VMAX = 200;
	}
	
	// Reset position and velocity
	if (_reset)
	{
		_reset = 0;
		position = Point(XSIZE / 2, YSIZE / 2);
		velocity = Point(-VMAX, 0);
	}

}

void CPong::draw()
{
	string score;
	static auto end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(33);

	// Clear canvas
	_canvas = _canvas.zeros(Size(XSIZE, YSIZE), CV_8UC3);

	// Display game over and reset parameters for new game
	if (gameover)
	{
		putText(_canvas, "GAME OVER", Point(XSIZE / 2 - 260, YSIZE / 2), FONT_HERSHEY_SIMPLEX, 3, Scalar::all(255), 3);
		imshow("Pong", _canvas);
		
		waitKey(4000);
		
		pong.lock();
		gameover = 0;
		position = Point (XSIZE / 2, YSIZE / 2);
		pong.unlock();

		_canvas = _canvas.zeros(Size(XSIZE, YSIZE), CV_8UC3);
	}

	// Draw paddles and ball in new position
	pong.lock();
	rectangle(_canvas, Point(paddle_center.x + PADWIDTH / 2, paddle_center.y + PADHEIGHT / 2), Point(paddle_center.x - PADWIDTH / 2, paddle_center.y - PADHEIGHT / 2), Scalar::all(255), CV_FILLED);
	rectangle(_canvas, Point(opponent_center.x + PADWIDTH / 2, opponent_center.y + PADHEIGHT / 2), Point(opponent_center.x - PADWIDTH / 2, opponent_center.y - PADHEIGHT / 2), Scalar::all(255), CV_FILLED);
	circle(_canvas, position, RADIUS, Scalar::all(255), CV_FILLED);
	pong.unlock();

	line(_canvas, Point(XSIZE / 2, YSIZE), Point(XSIZE / 2, 0), Scalar::all(255), 2);

	// Update frame count based on elsapsed update time
	frame_time = ((double)getTickCount() - frame_time) / getTickFrequency();

	if (count > 5)
	{
		stringstream stream;
		stream << fixed << setprecision(2) << ((1 / frame_time) - 2);
		frames = "FPS: " + stream.str();
		count = 0;
	}

	frame_time = getTickCount();
	
	pong.lock();
	score = "Score: " + to_string(player_score) + " to " + to_string(npc_score);
	pong.unlock();

	// Add score and frame count on screen
	putText(_canvas, score, Point(100, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar::all(255));
	putText(_canvas, frames, Point(XSIZE - 240, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar::all(255));
	
	// Display image
	imshow("Pong", _canvas);
	ch = waitKey(1);
	
	// Sleep for remaining time to achieve 30 FPS
	std::this_thread::sleep_until(end_time);

	// Reset end time
	end_time = std::chrono::steady_clock::now() + std::chrono::milliseconds(30);

	// Increment frame count
	count += 1;
}

void CPong::update_thread(CPong* ptr)
{
	while (ptr->thread_exit == false)
	{
		ptr->update();
	}
}

void CPong::draw_thread(CPong* ptr)
{

	while (ptr->thread_exit == false && ptr->ch != 'q')
	{
		ptr->draw();
	}

	ptr->thread_exit = true;
	exit(0);
}