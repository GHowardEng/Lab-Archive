#pragma once
#include "stdafx.h"
#include "CGameObject.h"
#include "CShip.h"

/**
*
* @brief Asteroid game object
*
*
* This class inherits from the CGameObject class to create an Asteroid object
*
* @author Grant Howard
*
*/
class CAsteroid : public CGameObject
{
public:
	/** @brief Overloaded draw function to differentiate asteroids from other objects.
	*
	* @param &im The Mat image to be drawn on.
	*
	* @return No return value.
	*
	*/
	void draw(Mat &im);

	/** @brief Overloaded wall collision test function, does not check for collision with top wall.
	*
	* @param &im The Mat image to be drawn on.
	*
	* @return No return value.
	*
	*/
	bool collide_wall(Size mat);
};