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
    
    void write(std::ostream &out)
    {
        int n = _solution.size();
        out.write((char *)&n, sizeof(n));
        out.write((char *)&_solution[0], _solution.size() * sizeof(State<T>));
    }

    void read(std::ifstream &in)
    {
        int n = 0;
        in.read((char *)&n, sizeof(n));

        State<T> tmp;
        for (int i = 0; i < n; ++i)
        {
            in.read((char *)&tmp, sizeof(tmp));
            _solution.push_back(tmp)
        }
    }

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
