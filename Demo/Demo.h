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

class Demo
{
public:
    Demo() {}
    ~Demo() {}

public:
    void run();
};
