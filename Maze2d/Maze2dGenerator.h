#pragma once
#include <string>
#include <vector>
#include <cstdlib>
#include <stack>
#include <random>

#include <chrono>
#include  <iomanip>

#include "Maze2d.h"
#include "Position.h"


/*
 * --------------------------------------------------------------------
 *       Class:  Maze2dGenerator
 *		 Description: This class is responsible to create a 2d maze.
 * --------------------------------------------------------------------
 */


class Maze2dGenerator
{
public:
	virtual Maze2d generate(const std::string& name, int length = 0, int width = 0) = 0;
	virtual std::string measureAlgorithmTime(std::string name,
		const int& width = 0, const int& height = 0) = 0;
};

/*
 * --------------------------------------------------------------------
 *       Class:  Maze2dGeneratorAbstract
 *		 Description: This class is responsible in implementing the time measurement algorithm of the maze creation
 * --------------------------------------------------------------------
 */
class Maze2dGeneratorAbstract : public Maze2dGenerator
{
public:
	Maze2dGeneratorAbstract(){}
	~Maze2dGeneratorAbstract(){}
public:
	virtual std::string measureAlgorithmTime(const std::string name, const int& width = 0, const int& height = 0);
};


/*
 * --------------------------------------------------------------------
 *       Class:  SimpleMaze2dGenerator
 *		 Description: This class implements the creation of a simple type 2d maze
 * --------------------------------------------------------------------
 */

class SimpleMaze2dGenerator : public Maze2dGeneratorAbstract
{
public:
	SimpleMaze2dGenerator() {};
	virtual ~SimpleMaze2dGenerator() {};

public:
	Maze2d generate(const std::string& name, int length = 0, int width = 0);
};

/*
 * --------------------------------------------------------------------
 *       Class:  SimpleMaze2dGenerator
 *		 Description: This class implements the creation of a type 2d maze
 * --------------------------------------------------------------------
 */


class MyMaze2dGenerator : public Maze2dGeneratorAbstract
{
public:
	MyMaze2dGenerator(){};
	virtual ~MyMaze2dGenerator(){};

public:
	Maze2d generate(const std::string& name, int length = 0, int width = 0);

};
