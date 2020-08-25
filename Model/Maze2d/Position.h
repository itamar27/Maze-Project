#pragma once
#include <iostream>

/*
 * --------------------------------------------------------------------
 *		Class: Position
 *		Description: This class is used to describe positions on 2 dimensional array.
 * --------------------------------------------------------------------
 */

class Position
{
public:
	Position() : _x(0), _y(0){};
	Position(const Position &p);
	Position(int x, int y) : _x(x), _y(y){};
	~Position(){};

public:
	int getX() const;
	int getY() const;
	void setX(int x);
	void setY(int y);

public:
	friend std::ostream &operator<<(std::ostream &out, const Position &p);
	Position &operator=(const Position &p);
	bool operator==(const Position &p) const;
	bool operator<(const Position& p) const;

private:
	int _x;
	int _y;
};
