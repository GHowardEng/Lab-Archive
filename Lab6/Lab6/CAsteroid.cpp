#include "stdafx.h"
#include "CAsteroid.h"

void CAsteroid::draw(Mat &im)
{
	circle(im, _position, _radius, _colour, 10);
}

bool CAsteroid::collide_wall(Size mat)
{
	if (_position.x - _radius < 0 || _position.x + _radius > mat.width || _position.y + _radius > mat.height)
	{
		return true;
	}

	else
	{
		return false;
	}

}

