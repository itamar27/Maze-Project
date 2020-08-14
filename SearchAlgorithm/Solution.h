#pragma once
#include <vector>

#include "State.h"


/*
 * --------------------------------------------------------------------
 *       Class: Solution
 *		 Description: This class is an generic class for holding a solution to an algorithm
 *                    in our case all the states that lad to the sultion of a maze.
 * --------------------------------------------------------------------
 */

template<class T>
class Solution
{
public:
    Solution(){};
    ~Solution(){};
public:
void insertState(State<T>& t){_solution.push_back(t);}

private:
    std::vector<State<T>> _solution;
};