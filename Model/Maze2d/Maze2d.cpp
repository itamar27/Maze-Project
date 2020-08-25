#include "Maze2d.h"


/* 
 *		Method: Maze2d
 *		Description: Maze2d full class constructor
 */
Maze2d::Maze2d(std::string name, Position entrance,
			   Position exit, std::vector<std::vector<int>> data)
	: _name(name), _entrance(entrance), _exit(exit), _data(data) {}

/*
 *		Method:  Maze2d 
 *		Description: copy constructor for class Maze2d
 */

Maze2d::Maze2d(const Maze2d &m2d)
{
	*this = m2d;
}

/*
 *		Method: operator=
 *		Description: overloading for assigment operator 
 */
Maze2d &Maze2d::operator=(const Maze2d &m2d)
{
	if (!m2d._name.empty())
		_name = m2d._name;

	if (m2d._entrance.getX() >= 0 && m2d._entrance.getY() >= 0)
		_entrance = m2d._entrance;

	if (m2d._exit.getX() >= 0 && m2d._exit.getY() >= 0)
		_exit = m2d._exit;

	if (!m2d._data.empty())
		_data = m2d._data;

	return *this;
}

/*
 *		Method:	operator<<
 *		Description: overloading for 'in' stream operator
 */

std::ostream &operator<<(std::ostream &out, const Maze2d &m2d)
{
	std::string str;

	for (int i = 0; i < m2d._data.size(); i++)
	{
		for (int j = 0; j < m2d._data[i].size(); j++)
		{
			if (m2d._data[i][j] == 1) //|| m2d._data[i][j] == 2)
				str += "||";

			else
				str += "  ";
		}
		str += "\n";
	}
	return out << '[' << m2d._name << "]\n"
			   << std::endl
			   << str << std::endl;
}

/*
 *		Method: getStartPosition()
 *		Description: return the entrance position of a maze 
 */

Position Maze2d::getStartPosition() const
{
	return _entrance;
}

/*
 *		Method: getGoalPosition()
 *		Description: return the goal position of a maze 
 */

Position Maze2d::getGoalPosition() const
{
	return _exit;
}

/*
 *		Method: getPossibleMoves() 
 *		Description: returns all availble moves for specific position on board
 */

std::string *Maze2d::getPossibleMoves(const Position &p) const
{
	//return value moves for each possible move
	std::string *moves = new std::string[4];

	//intializing everystring on move
	for (int i = 0; i < 4; i++)
		moves[i] = "";

	int x = p.getX();
	int y = p.getY();

	if (x < 0 || y < 0 || x > _data.size() - 1 || y > (_data[_data.size() - 1].size() - 1))
		throw "Not a valid Position";

	if (_data[x][y] == 1)
		throw "This position is a wall";

	if ((x - 1) >= 0 && _data[x - 1][y] == 0)
		moves[0] = "up";

	if ((x + 1) <= (_data.size() - 1) && _data[x + 1][y] == 0)
		moves[1] = "down";

	if ((y - 1) >= 0 && _data[x][y - 1] == 0)
		moves[2] = "left";

	if ((y + 1) <= (_data[_data.size() - 1].size() - 1) && _data[x][y + 1] == 0)
		moves[3] = "right";

	return moves;
}

/*
 *		Method: getMazeName() 
 *		Description: return the name of the Maze
 */

std::string Maze2d::getMazeName() const
{
	return _name;
}

/*
 *		Method: getData() 
 *		Description: return a 2d vector array
 */

std::vector<std::vector<int>> Maze2d::getData() const
{
	return _data;
}