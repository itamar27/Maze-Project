#pragma once

#include "SearchAlgorithm.h"
#include "Heuristic.h"

/*
 * --------------------------------------------------------------------
 *      Class: A*
 *      Description: This class implements a generic A* algorithm for any kind of searcherable class
 * --------------------------------------------------------------------
 */

template <class T>
class Astar : public CommonSearcher<T>
{

public:
    Astar(Heuristic<T> *h) : CommonSearcher<T>()
    {
        _h = h;
    }

    virtual ~Astar() { delete _h; };

public:
    virtual Solution<T> solve(Searchable<T> *s)
    {
        if (s == nullptr)
            throw "Not a Valid pointer";

        State<T> goal = s->getGoalState();
        State<T> start = s->getStartState();
        State<T> u;

        std::vector<State<T>> moves; // Will use to get all the next possible states of the problem
        this->_openList.push(start);

        auto cmp = [](State<T> a, State<T> b) { return a.getState() < b.getState(); }; // lambda function to compare states
        std::set<State<T>, decltype(cmp)> closedList(cmp);                             // set to hold states and ask if they're in it (for evaluated states)
        std::set<State<T>, decltype(cmp)> copyOpenList(cmp);                           // set to hold states and ask if they're in it (represents this->_openList)

        copyOpenList.insert(s->getStartState());

        while (!(this->_openList.empty()))
        {
            u = this->popList();
            copyOpenList.erase(copyOpenList.find(u));
            closedList.insert(u);

            if (u == goal)
                break; // build solution outside of loop

            moves = s->getAllPossibleStates(u);

            for (int i = 0; i < moves.size(); ++i)
            {

                auto itClosed = closedList.find(moves[i]);
                auto itOpen = copyOpenList.find(moves[i]);

                if ((itClosed == closedList.end()) && (itOpen == copyOpenList.end()))
                {

                    moves[i].setCameFrom(u);
                    u.calculateCost(moves[i], _h->calc(moves[i], goal));
                    this->_openList.push(moves[i]);
                    copyOpenList.insert(moves[i]);
                }

                else if (u.getCost() + 1 + _h->calc(u, goal) < moves[i].getCost())
                {
                    if (itOpen == copyOpenList.end())
                    {
                        this->_openList.push(moves[i]);
                        copyOpenList.insert(moves[i]);
                    }

                    moves[i].setCameFrom(u);

                    u.calculateCost(moves[i], _h->calc(moves[i], goal));
                }
            }
        }

        if (!(u == goal)) // Checks if the problem got a solution at al
            throw "Unsolveable";

        Solution<T> sol;
        State<T> tmpState;
        tmpState = u;

        while (!(tmpState == start)) // Building Solution by backtracking the parents states
        {
            sol.insertState(tmpState);
            tmpState = tmpState.getCameFrom();
        }

        sol.insertState(tmpState);
        tmpState = tmpState.getCameFrom();
        return sol;
    }

private:
    Heuristic<T> *_h;
};