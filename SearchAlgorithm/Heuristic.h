#pragma once

#include "State.h"

template <class T>
class Heuristic
{
public:
   virtual double calc(State<T> &state, State<T> &goal);
};
