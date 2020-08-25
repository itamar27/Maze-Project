#pragma once

#include "State.h"

/*
 * --------------------------------------------------------------------
 *      Class: Heuristic
 *      Description: This class is an interface 
 *                   for every Heuristic algorithm that is beign used in search problome
 * --------------------------------------------------------------------
 */

template <class T>
class Heuristic
{
public:
   virtual double calc(State<T> &state, State<T> &goal);
};
