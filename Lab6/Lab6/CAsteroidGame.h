#pragma once
#include "stdafx.h"
#include "CBase4618.h"
#include "CAsteroid.h"
#include "CMissile.h"
#include "CShip.h"


/**
*
* @brief Uses openCV and CGameObjects to play a game of Asteroids.
*
*
* This class inherits from the CBase4618 class and overloads functions to implement the classic 'Asteroids' game. Requires openCV.
*
*
* @author Grant Howard
*
*/
class CAsteroidGame: public CBase4618
{
private:
	double _time;
	double _loop = (double)getTickCount();
	double _runtime;
	double _starttime = (double)getTickCount();
	double _spawntime;
	double _spawnref = (double)getTickCount();

	int _score = 0;
	int _reset = 0;
	int gameover = 0;

	vector<CAsteroid> asteroid;
	vector<CMissile> missile;
	CShip ship;
public:
	/** @brief Constructor to initiallize size of canvas and GameObject parameters.
	*
	* @param mat Dimensions of canvas (width, height).
	*
	*
	* @return No return value.
	*
	*/
	CAsteroidGame(Size mat);

	/** @brief Reads joystick inputs and updates velocity/positions for all game objects.
	*
	* @return No return value.
	*
	*/
	void update();

	/** @brief Uses updated coordinates to draw objects and displays image.
	*
	* @return No return value.
	*
	*/
	void draw();

	/** @brief Runs program by calling update() and draw() in a loop.
	*
	* @return No return value.
	*
	*/
	void run();
};