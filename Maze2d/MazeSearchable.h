#pragma once
#include <vector>

#include "Maze2d.h"
#include "../SearchAlgorithm/Searchable.h"

/*
 * --------------------------------------------------------------------
 *       Class: MazeSearchAble
 *		 Description: This class is a structural design pattern - Adapter, between Maze2d and Searchable
 * --------------------------------------------------------------------
 */

template <class T>
class MazeSearchable : public Searchable<T>
{
public:
    MazeSearchable(Maze2d &m2d) : _m2d(m2d) {}
    ~MazeSearchable() {}

public:
    virtual State<T> &getStartState() const { return _m2d.getStartPosition(); }
    virtual State<T> &getGoalState() const { return _m2d.getGoalPosition(); }
    virtual std::vector<State<T>> &getAllPossibleStates(State<T> &s) const { return s; };

    private : Maze2d _m2d;
};
