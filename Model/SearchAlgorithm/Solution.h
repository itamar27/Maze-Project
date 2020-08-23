#pragma once
#include <vector>
#include <iostream>
#include <string>

#include "State.h"

/*
 * --------------------------------------------------------------------
 *       Class: Solution
 *		 Description: This class is an generic class for holding a solution to an algorithm
 *                    in our case all the states that lad to the sultion of a maze.
 * --------------------------------------------------------------------
 */

template <class T>
class Solution
{
public:
    Solution(){};
    Solution(const Solution<T> &sol)
    {
        this->_solution = sol._solution;
    };
    ~Solution(){};

public:
    void insertState(State<T> &t) { _solution.insert(_solution.begin(), t); }

    template <typename U>
    friend std::ostream &operator<<(std::ostream &out, const Solution<U> &sol);

public:
    int getSolutionSize() const { return _solution.size(); }

private:
    std::vector<State<T>> _solution;
};

template <typename U>
std::ostream &operator<<(std::ostream &out, const Solution<U> &sol)
{
    auto it = sol._solution.begin();
    std::string str;

    int count = 0;
    while (it != sol._solution.end())
    {
        out << "-->" << it->getState();
        if (count++ == 5)
        {
            std::cout << std::endl;
            count = 0;
        }
        it++;
    }

    return out;
}
