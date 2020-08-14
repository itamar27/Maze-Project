#pragma once
#include "State.h"

/*
 * --------------------------------------------------------------------
 *       Class: Searchable
 *		 Description: This class is an interface for search problomes(Such as maze).
 * --------------------------------------------------------------------
 */

template<class T>
class Searchable
{
public:
    virtual State<T>& getStartState() = 0;
    virtual State<T>& getGoalState() = 0;
    virtual std::vector<State<T>> getAllPossibleStates(State<T>& s) = 0;
};
