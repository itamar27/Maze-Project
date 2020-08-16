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
        double row = abs(state.getState().getX() - goal.getState().getX());
        double col = abs(state.getState().getY() - goal.getState().getY());
        return (row + col);
    }
};

class AriealDistance : public Heuristic<Position>
{
public:
    virtual double calc(State<Position> &state, State<Position> &goal)
    {
        double gValue = state.getCost() - state.getCameFrom().getCost();
        double row = abs(state.getState().getX() - goal.getState().getX());
        double col = abs(state.getState().getY() - goal.getState().getY());
        double root = (pow(row, 2) + pow(col, 2));

        return root * gValue;
    }
};