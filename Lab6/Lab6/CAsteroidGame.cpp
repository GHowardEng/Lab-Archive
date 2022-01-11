#include "stdafx.h"
#include "CAsteroidGame.h"

#define ship_radius 10
#define ship_lives 5

#define missile_radius 4

#define WHITE Scalar::all(255)
#define RED Scalar (0, 0, 255)

#define YOFFSET	494
#define XOFFSET 506

CAsteroidGame::CAsteroidGame(Size mat) 
{
	_canvas = Mat::zeros(mat, CV_8UC3);

	if (!controller.open("COM5"))
	{
		exit(0);
	}

	ship.set_rad(ship_radius);
	ship.set_lives(ship_lives);
	ship.set_colour(WHITE);
	ship.set_vel(Point2f(0, 0));
	ship.move(Point2f(XSIZE / 2, YSIZE / 2));
}

void CAsteroidGame::update()
{
	static int value1 = XOFFSET;
	static int value2 = YOFFSET;
	int wall;

	_time = ((double)getTickCount() - _loop) / getTickFrequency();
	_runtime = ((double)getTickCount() - _starttime) / getTickFrequency();
	_loop = getTickCount();
	
	controller.get_analog(15, value1);
	controller.get_analog(9, value2);

	ship.set_vel(ship.get_vel()*0.95);
	ship.set_vel(ship.get_vel() + Point2f(5 * (value1 - XOFFSET)*_time, -5 * (value2 - YOFFSET)*_time));

	if (_runtime > 0.1)
	{

		if (controller.get_button(32, 0))
		{
			cout << "\nMissile (" << missile.size() << ")";
			CMissile temp_missile;

			temp_missile.set_vel(Point2f(0, -400));
			temp_missile.set_colour(RED);
			temp_missile.move(ship.get_pos() - Point2f(0, ship.get_rad()));
			temp_missile.set_rad (missile_radius);

			missile.push_back(temp_missile);
		}

		if (controller.get_button(33, 1))
		{
			cout << "\nReset";
			_reset = 1;
			ship.set_lives(ship_lives);
			_score = 0;
		}

		_starttime = getTickCount();
	}
	
	for (int index = 0; index < missile.size(); index++)
	{
		missile[index].move(missile[index].get_pos() + missile[index].get_vel() * _time);
		
		for (int astro_index = 0; astro_index < asteroid.size(); astro_index++)
		{
			if (index < missile.size() && astro_index < asteroid.size() && missile[index].collide(asteroid[astro_index]))
			{
				missile.erase(missile.begin() + index);

				_score += 0.3*asteroid[astro_index].get_rad();
				asteroid.erase(asteroid.begin() + astro_index);
			}
			else if (index < missile.size() && missile[index].collide_wall(Size(XSIZE, YSIZE)))
			{
				missile.erase(missile.begin() + index);
			}
		}
	}

	for (int index = 0; index < asteroid.size(); index++)
	{
		asteroid[index].move(asteroid[index].get_pos() + asteroid[index].get_vel() * _time);
		
		if (asteroid[index].collide_wall(Size (XSIZE, YSIZE)))
		{
			asteroid.erase(asteroid.begin() + index);
		}

		else if (asteroid[index].collide(ship))
		{
			asteroid.erase(asteroid.begin() + index);
			_reset = 1;
			ship.hit();
		}
	}

	if (ship.get_lives() == 0)
	{
		gameover = 1;
		_reset = 1;

		ship.set_lives(ship_lives);
		_score = 0;
	}

	ship.move(ship.get_pos() + ship.get_vel()*_time);

	wall = ship.collide_wall(Size(XSIZE, YSIZE));

	if (wall == top)
	{
		ship.move(Point2f(ship.get_pos().x, YSIZE + ship.get_rad()));
	}
	else if (wall == bottom)
	{
		ship.move(Point2f(ship.get_pos().x, 0 - ship.get_rad()));
	}
	else if (wall == left)
	{
		ship.move(Point2f(XSIZE + ship.get_rad(), ship.get_pos().y));
	}
	else if (wall == right)
	{
		ship.move(Point2f(0 - ship.get_rad(), ship.get_pos().y));
	}

	if (_reset)
	{
		_reset = 0;

		missile.clear();
		asteroid.clear();

		ship.move(Point2f(XSIZE / 2, YSIZE / 2));
		ship.set_vel(Point2f(0, 0));

		_starttime = getTickCount();
		_spawnref = getTickCount();
	}
}

void CAsteroidGame::draw()
{
	_canvas = Mat::zeros(Size(XSIZE, YSIZE), CV_8UC3);

	ship.draw(_canvas);

	for (int index = 0; index < asteroid.size(); index ++)
	{
		asteroid[index].draw(_canvas);
	}

	for (int index = 0; index < missile.size(); index++)
	{
		missile[index].draw(_canvas);
	}

	if (gameover)
	{
		_canvas = _canvas.zeros(Size(XSIZE, YSIZE), CV_8UC3);

		putText(_canvas, "GAME OVER", Point(XSIZE / 2 - 260, YSIZE / 2), FONT_HERSHEY_SIMPLEX, 3, Scalar::all(255), 3);
		imshow("Asteroids", _canvas);
		
		while (!controller.get_button(33, 1) && waitKey(1) != 'q');

		gameover = 0;
		_canvas = _canvas.zeros(Size(XSIZE, YSIZE), CV_8UC3);
		_reset = 1;
	}

	string lives = "Lives: " + to_string(ship.get_lives());
	string score = "Score: " + to_string(_score);
	
	putText(_canvas, lives, Point(10, 30), FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);
	putText(_canvas, score, Point(150, 30), FONT_HERSHEY_SIMPLEX, 0.5, WHITE, 1);
	imshow("Asteroids", _canvas);
}

void CAsteroidGame::run()
{
	do
	{
		_spawntime = ((double)getTickCount() - _spawnref) / getTickFrequency();

		if (_spawntime > 2)
		{
			_spawnref = (double)getTickCount();

			CAsteroid astro;

			int num = rand() % 155;

			astro.set_rad(((float)rand() / (float)RAND_MAX) * 50 + 10);
			astro.set_vel(Point2f(((float)rand() / (float)RAND_MAX) * 200 - 100, ((float)rand() / (float)RAND_MAX) * 100 + 50));
			astro.set_colour (Scalar(num + 20, num + 20, num + 20));
			astro.move(Point2f(XSIZE / 2 - 300 + rand() % 600, 0 - astro.get_rad()));

			asteroid.push_back(astro);

			cout << "\nAsteroid (" << asteroid.size() << ")";
		}
		update();
		draw();
	} while (waitKey(1) != 'q');
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