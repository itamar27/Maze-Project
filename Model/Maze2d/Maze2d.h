#pragma once
#include <string>
#include <vector>
#include <iostream>

#include "Position.h"

/*
 * --------------------------------------------------------------------
 *       Class:  Maze2d
 *		 Description: This class is responsible to hold data on any form of 2 dimension maze.
 * --------------------------------------------------------------------
 */

class Maze2d
{
public:
	Maze2d(std::string name, Position entrance, Position exit, std::vector<std::vector<int>> data);
	Maze2d(const Maze2d &m2d);
	~Maze2d(){};

public:
	Position getStartPosition() const;
	Position getGoalPosition() const;
	std::string *getPossibleMoves(const Position &p) const;
	std::string getMazeName() const;
	std::vector<std::vector<int>> getData() const;

public:
	friend std::ostream &operator<<(std::ostream &out, const Maze2d &m2d);
	Maze2d &operator=(const Maze2d &m2d);

private:
	std::string _name;
	Position _entrance;
	Position _exit;
	std::vector<std::vector<int>> _data;
};
