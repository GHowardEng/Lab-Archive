#pragma once
#include "stdafx.h"
#include "CGameObject.h"

#define top 0
#define bottom 1
#define left 2
#define right 3

/**
*
* @brief Ship game object
*
*
* This class inherits from the CGameObject class to create a Ship object
*
* @author Grant Howard
*
*/
class CShip : public CGameObject
{
public:
	/** @brief Overloaded collision function returns side where collision occured.
	*
	* @param mat The size of the image to be tested.
	*
	* @return Returns int representing side of collision.
	*
	*/
	int collide_wall(Size mat);
};