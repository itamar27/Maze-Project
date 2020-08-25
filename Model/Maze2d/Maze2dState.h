#pragma once 

#include "../SearchAlgorithm/State.h"
#include "Position.h"

/*
 * --------------------------------------------------------------------
 *      Class: Maze2dState
 *      Description:This class is a class for claculating the next state for each state on maze board 
 * --------------------------------------------------------------------
 */

class Maze2dState : public State<Position>
{
public:
    Maze2dState(Position state) : State<Position>(state) {}
    ~Maze2dState() {}
    
};

