#pragma once
#include <string>
#include <memory>

#include "../Maze2d/Position.h"

/*
 * --------------------------------------------------------------------
 *       Class: State
 *		 Description:This class is an generic class for determing the cost of state in the algorithm
 *                   what was this state;  
 * --------------------------------------------------------------------
 */

template <class T>
class State
{
public:
    State(T state) : _state(state), _cost(0), _camefrom(nullptr) {}
    virtual ~State() {}

public:
    bool operator==(State &s) { return _state == s._state; }
    bool operator<(State &s) { return _cost < s._cost; }

public:
    double getCost() { return _cost; }
    State<T>* getFatherNode() { return _camefrom; }

protected:
    T _state;
    double _cost;
    State<T> *_camefrom; //Not a unique_ptr need to remember deleting this object
};

/*
 * --------------------------------------------------------------------
 *       Class: Maze2dState
 *		 Description:This class is a class for claculating the next state for each state on maze board 
 * --------------------------------------------------------------------
 */

template <class T>
class Maze2dState : public State<T>
{
public:
    Maze2dState(Position state) : State<T>(state) {}
    ~Maze2dState() {}

public:
    double calculateCost(State<T> &state)
    {
        if (state.getFatherNode() == nullptr)
            throw "Not a Valid Pointer";

        return state.getFatherNode()->getCost() + 1;
    } 
};