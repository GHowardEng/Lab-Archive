#include "stdafx.h"
#include "CGameObject.h"

void CGameObject::move(Point2f pos)
{
	_position = pos;
}

void CGameObject::hit()
{
	_lives -= 1;
}

void CGameObject::draw(Mat &im)
{
	circle(im, _position, _radius, _colour);
}

bool  CGameObject::collide_wall(Size mat)
{
	if (_position.x + _radius < 0 || _position.x - _radius > mat.width || _position.y + _radius < 0 || _position.y - _radius > mat.height)
	{
		return true;
	}

	else
	{
		return false;
	}
}

bool CGameObject::collide(CGameObject &obj)
{
	if ((abs(obj.get_pos().x - _position.x) < obj._radius + _radius) && (abs(obj.get_pos().y - _position.y) < obj._radius + _radius))
	{
		return true;
	}

	else
	{
		return false;
	}
}
