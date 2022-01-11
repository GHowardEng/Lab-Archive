#include "stdafx.h"
#include "CShip.h"



int CShip::collide_wall(Size mat)
{
	if (_position.x + _radius < 0 )// || _position.x - _radius > mat.width || _position.y - _radius > mat.height)
	{
		return left;
	}

	else if (_position.x - _radius > mat.width)
	{
		return right;
	}

	else if (_position.y - _radius > mat.height)
	{
		return bottom;
	}

	else if (_position.y + _radius < 0)
	{
		return top;
	}
}