#include <string>
#include <memory>

#include "./Position.h"


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
    State(T state) : _state(state), _cost(0), _camefrom(nullptr){};
    ~State(){};

public:
    bool operator==(State &s) { return _state == s._state; }

private:
    T _state;
    double _cost;
    std::unique_ptr<State> _camefrom
};