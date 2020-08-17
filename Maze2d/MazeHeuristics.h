#pragma once
#include <cstdlib>
#include <math.h>

#include "Maze2dState.h"
#include "../SearchAlgorithm/Heuristic.h"
#include "Position.h"



class ManahattanDistance : public Heuristic<Position>
{
public:
    virtual double calc(State<Position> &state, State<Position> &goal)
    {

        double row = fabs(state.getState().getX() - goal.getState().getX());
        double col = fabs(state.getState().getY() - goal.getState().getY());

        return (row + col);
    }
};

class AriealDistance : public Heuristic<Position>
{
public:
    virtual double calc(State<Position> &state, State<Position> &goal)
    {

        double gValue = fabs(state.getCost() - state.getCameFrom().getCost());
        double row = fabs(state.getState().getX() - goal.getState().getX());
        double col = fabs(state.getState().getY() - goal.getState().getY());
        double root = sqrt((row*row) + (col*col));


        return root * gValue;
    }
};