#pragma once
#include <vector>

#include "Position.h"
#include "Maze2d.h"
#include "Maze2dState.h"
#include "../SearchAlgorithm/Searchable.h"

/*
 * --------------------------------------------------------------------
 *       Class: MazeSearchAble
 *		 Description: This class is a structural design pattern - Adapter, between Maze2d and Searchable
 * --------------------------------------------------------------------
 */

class MazeSearchable : public Searchable<Position>
{
public:
    MazeSearchable(Maze2d &m2d) : _m2d(m2d) {}
    ~MazeSearchable() {}

public:
    virtual const State<Position> getStartState() const { return _m2d.getStartPosition(); }
    virtual const State<Position> getGoalState() const { return _m2d.getGoalPosition(); }
    virtual std::vector<State<Position>> getAllPossibleStates(State<Position> &s)
    {
        Position tmp = s.getState();
        int x = tmp.getX();
        int y = tmp.getY();
        std::string *moves = _m2d.getPossibleMoves(tmp);
        std::vector<State<Position>> allMoves;

        for (int i = 0; i < 4; i++)
        {

            if (moves[i] == "")
                continue;
            if (moves[i] == "up")
                allMoves.push_back(Position(x - 1, y));
           else if (moves[i] == "down")
                allMoves.push_back(Position(x + 1, y));
            else if (moves[i] == "left")
                allMoves.push_back(Position(x, y - 1));
            else if (moves[i] == "right")
                allMoves.push_back(Position(x, y + 1));
        }

        return allMoves;
    };

private:
    Maze2d _m2d;
};
