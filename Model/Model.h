#pragma once
#include <map>
#include <iostream>

#include "Observable.h"
#include "./Maze2d/Position.h"
#include "./Maze2d/Maze2d.h"
#include "./Maze2d/Maze2dGenerator.h"
#include "./Maze2d/Maze2dState.h"
#include "./Maze2d/MazeSearchable.h"
#include "./Maze2d/MazeHeuristics.h"
#include "./SearchAlgorithm/Astar.h"
#include "./SearchAlgorithm/BFS.h"
#include "./SearchAlgorithm/Solution.h"
#include "./Maze2d/MazeCompression.h"
#include "./Demo/Demo.h"

/*
 * --------------------------------------------------------------------
 *      Class:  Model
 *      Description: class that is used as an interface to the Model part in MVC pattern.
 * --------------------------------------------------------------------
 */

class Model : public Observable
{
public:
    virtual void generateMaze(std::string s, int len, int width) = 0;
    virtual Maze2d* getMaze(std::string s) = 0;
    virtual void saveMaze(std::string name, std::ofstream *oFile) = 0;
    virtual void loadMaze(std::ifstream *iFile, std::string name) = 0;
    virtual int getMazeSize(std::string name) = 0;
    virtual int getFileSize(std::string name) = 0;
    virtual void solve(std::string name, std::string algorithm) = 0;
    virtual Solution<Position> displaySolution(std::string name) = 0;
};

/*
 * --------------------------------------------------------------------
 *       Class:  MyModel
 *		 Description: class that is being used to implement Model interface.
 * --------------------------------------------------------------------
 */

class MyModel : public Model
{
public:
    MyModel() {}
    ~MyModel();

public:
    virtual void generateMaze(std::string s, int len = 0, int width = 0);
    virtual Maze2d* getMaze(std::string s);
    virtual void saveMaze(std::string name, std::ofstream *oFile);
    virtual void loadMaze(std::ifstream *iFile, std::string name = "");
    virtual int getMazeSize(std::string name);
    virtual int getFileSize(std::string name);
    virtual void solve(std::string name, std::string algorithm);
    virtual Solution<Position> displaySolution(std::string name);
    
    virtual void saveAllMazes(std::ofstream *saveFile);
    virtual void loadAllMazes(std::ifstream *loadFile);
    virtual void runDemo();

private:
    std::map<std::string, Solution<Position> *> _solutions;
    std::map<std::string, Maze2d *> _mazes;
};
