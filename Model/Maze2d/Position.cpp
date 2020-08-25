#include "Position.h"

Position::Position(const Position &p)
{
	*this = p;
}

int Position::getX() const
{
	return _x;
}

int Position::getY() const
{
	return _y;
}

void Position::setX(int x)
{
	if (x >= 0)
		_x = x;
	else
		throw "Not a valid value";
}

void Position::setY(int y)
{
	if (y >= 0)
		_y = y;
	else
		throw "Not a valid value";
}

/*
 *		Method: operator<< 
 *		Description: overloading operator<< for position class 
 */

std::ostream &operator<<(std::ostream &out, const Position &p)
{
	return out << "{" << p._x << "," << p._y << "}";
}

/*
 *		Method: operator= 
 *		Description: overloading operator= for position class 
 */
Position &Position::operator=(const Position &p)
{
	_x = p._x;
	_y = p._y;

	return *this;
}

/*
 *		Method: operator== 
 *		Description: overloading operator== for position class 
 */

bool Position::operator==(const Position &p) const
{
	return ((_x == p._x) && (_y == p._y));
}

/*
 *		Method: operator< 
 *		Description: overloading operator< for position class 
 */
bool Position::operator<(const Position &p) const
{
	bool t = false;

	if (_y == p._y)
	{
		if (_x < p._x)
			t = true;
	}
	else if (_y < p._y)
		t = true;

	return t;
}