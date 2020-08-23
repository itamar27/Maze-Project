#pragma once
#include <iostream>

#include "../Maze2d/Position.h"
#include "../Maze2d/Maze2dState.h"
#include "../Maze2d/MazeHeuristics.h"
#include "../Maze2d/MazeSearchable.h"
#include "../Maze2d/Maze2dGenerator.h"
#include "../Maze2d/Maze2d.h"
#include "../SearchAlgorithm/BFS.h"
#include "../SearchAlgorithm/Astar.h"

/*
 * --------------------------------------------------------------------
 *       Class:  Demo
 *		 Description: class That can run a demo of maze generation and solving it.
 * --------------------------------------------------------------------
 */

class Demo
{
public:
    Demo() {}
    ~Demo() {}

public:
    void run();
};
