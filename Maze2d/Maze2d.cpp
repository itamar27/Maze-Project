#include "Maze2d.h"


/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d full class constructor
 * --------------------------------------------------------------------
 */
Maze2d::Maze2d(std::string name, Position entrance,
	Position exit, Position player, std::vector<std::vector<int>> data)
	: _name(name), _entrance(entrance), _exit(exit), _player(player), _data(data) {}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d copy constructor
 * --------------------------------------------------------------------
 */

Maze2d::Maze2d(const Maze2d& m2d)
{
	*this = m2d;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d = operator
 * --------------------------------------------------------------------
 */
Maze2d& Maze2d::operator=(const Maze2d& m2d)
{
	if (!m2d._name.empty())
		_name = m2d._name;

	if (m2d._entrance.getX() >= 0 && m2d._entrance.getY() >= 0)
		_entrance = m2d._entrance;

	if (m2d._exit.getX() >= 0 && m2d._exit.getY() >= 0)
		_exit = m2d._exit;

	if (m2d._player.getX() >= 0 && m2d._player.getY() >= 0)
		_player = m2d._player;

	if (!m2d._data.empty())
		_data = m2d._data;
	return *this;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d = operator
 * --------------------------------------------------------------------
 */

std::ostream& operator<<(std::ostream& out, const Maze2d& m2d)
{
	std::string str;

	for (int i= 0; i < m2d._data.size(); i++)
	{
		for (int j = 0; j< m2d._data[i].size(); j++)
		{
			if(m2d._data[i][j] == 1 || m2d._data[i][j] == 2)
				str += "# ";
			
			else 
				str += "  ";
		}
		str += "\n";
	}
	return 	out << '[' << m2d._name << "]\n"<< std::endl<< str <<std::endl;
}


/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d getStartPosition()
 * --------------------------------------------------------------------
 */

Position Maze2d::getStartPosition() const {
	return _entrance;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d getGoalPosition()
 * --------------------------------------------------------------------
 */

Position Maze2d::getGoalPosition() const
{
	return _exit;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d getPossibleMoves() returns all availble moves for specific position on board
 * --------------------------------------------------------------------
 */

std::string* Maze2d::getPossibleMoves(const Position& p) const
{
	//return value moves for each possible move
	std::string* moves =new std::string[4];
	
	//intializing everystring on move
	for(int i=0; i<4; i++)
		moves[i] = "";


	int x = p.getX();
	int y = p.getY();

	if (x < 0 || y < 0 || x > _data.size() - 1 || y >(_data[_data.size()-1].size()-1))
		throw "Not a valid Position";

	if (_data[x][y] == 1)
		throw "This position is a wall";

	if ((x-1) >= 0 && _data[x-1][y] == 0)
		moves[0] = "up";

	if ((x+1) <= (_data.size()-1) && _data[x+1][y] == 0)
		moves[0] = "down";

	if ((y-1) >= 0 && _data[x][y-1] == 0)
		moves[0] = "left";

	if ((y+1) <= (_data[_data.size()-1].size() -1) && _data[x][y+1] == 0)
		moves[0] = "right";

	return moves;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d getMazeName() return the name of the Maze
 * --------------------------------------------------------------------
 */

std::string Maze2d::getMazeName() const
{
	return _name;
}

/*
 * --------------------------------------------------------------------
 *       Method:  Maze2d getData() return a 2d int array
 * --------------------------------------------------------------------
 */

int** Maze2d::getData() const
{
	int** tmp = new int*[_data.size()];

	for (int i= 0; i < _data.size(); i++)
	{
		tmp[i] = new int[_data[i].size()];
	}



	for (int i= 0; i < _data.size(); i++)
	{
		for (int j = 0; j < _data[i].size(); j++)
		{
			tmp[i][j] = _data[i][j];
		}
	}

	return tmp; // these 2d array is deleted in the compression class function


}