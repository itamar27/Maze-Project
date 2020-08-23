#pragma once
#include <map>
#include <iostream>

#include "Observable.h"
#include "./Maze2d/Position.h"
#include "./Maze2d/Maze2d.h"
#include "./SearchAlgorithm/Solution.h"
#include "Demo/Demo.h"
#include "./Maze2d/MazeCompression.h"

/*
 * --------------------------------------------------------------------
 *       Class:  Model
 *		 Description: class that is used as an interface to the Model part in MVC pattern.
 * --------------------------------------------------------------------
 */

class Model : public Observable
{
public:
    virtual void generateMaze(std::string s) = 0;
    virtual Maze2d &getMaze(std::string s) = 0;
    virtual void saveMaze(std::string name, std::string filename) = 0;
    virtual void loadMaze() = 0;
    virtual void getMazeSize() = 0;
    virtual void solve() = 0;
    virtual void displaySolution() = 0;
    virtual void getFileSize() = 0;
    //virtual void runDemo() = 0;
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
    virtual void generateMaze(std::string s);
    virtual Maze2d &getMaze(std::string s);
    virtual void saveMaze(std::string name, std::string filename);
    virtual void loadMaze(std::string filename, std::string name);
    virtual void getMazeSize();
    virtual void solve();
    virtual void displaySolution();
    virtual void getFileSize();
    //virtual void runDemo();

private:
    std::map<std::string, Solution<Position> *> _solutions;
    std::map<std::string, Maze2d *> _mazes;
};