#pragma once
#include <string>

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
    State() {}
    State(T state) : _state(state), _cost(0) {}
    State(const State<T> &s) : _state(s._state), _cost(s._cost), _camefrom(_camefrom) {}
    virtual ~State() {}

    // A generic implemntation for calculate cost adding 1 to the next state.
    // if required another implementation override this function
    //  for this users module you can use the set and get function for _cost date memeber
public:
    virtual double calculateCost(State &targetState)
    {
        targetState._cost = _cost + 1;
        return _cost + 1;
    };

public:
    double getCost() const { return _cost; }
    void setCost(double cost)
    {
        if (_camefrom->cost <= cost)
            _cost = cost;
        else
            throw "Not a valid cost";
    }

    void setCameFrom(State<T> &s)
    {
        std::cout<<"state sent to set camefrom: "<<s.getState()<<std::endl;
        _camefrom = new State<T>(s);
        std::cout<<"New came from value: "<<_camefrom->getState()<<std::endl;
    }

    State<T>* getCameFrom()
    {
        return _camefrom;
    }

    const T &getState() { return _state; }

public:
    bool operator==(State<T> &s) const { return _state == s._state; }
    bool operator<(const State<T> &s) const { return _cost < s._cost; }
    bool operator>(const State<T> &s) const { return _cost > s._cost; }

protected:
    T _state;
    double _cost;
    State<T> *_camefrom;
};

