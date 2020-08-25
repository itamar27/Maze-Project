#pragma once

#include "SearchAlgorithm.h"

/*
 * --------------------------------------------------------------------
 *      Class: BFS
 *      Description: This class implements a generic BFS algorithm for any kind of searcherable class
 * --------------------------------------------------------------------
 */

template <class T>
class BFS : public CommonSearcher<T>
{
public:
    BFS() : CommonSearcher<T>() {}
    virtual ~BFS(){};

public:
    virtual Solution<T> solve(Searchable<T> *s);
};


template <class T>
Solution<T> BFS<T>::solve(Searchable<T> *s)
{
    if (s == nullptr)
        throw "Not a Valid pointer";

    State<T> goal = s->getGoalState();
    State<T> start = s->getStartState();
    State<T> u;
    std::vector<State<T>> moves;
    this->_openList.push(start);

    auto cmp = [](State<T> a, State<T> b) { return a.getState() < b.getState(); };
    std::set<State<T>, decltype(cmp)> closedList(cmp);
    std::set<State<T>, decltype(cmp)> copyOpenList(cmp); // Hash set to hold states and ask if they're in its (represents this->_openList)

    copyOpenList.insert(s->getStartState());

    while (!(this->_openList.empty()))
    {
        u = this->popList();
        copyOpenList.erase(copyOpenList.find(u));
        closedList.insert(u);
        if (u == goal)
            break; // build sultion outside of loop

        moves = s->getAllPossibleStates(u);

        for (int i = 0; i < moves.size(); ++i)
        {

            auto itClosed = closedList.find(moves[i]);
            auto itOpen = copyOpenList.find(moves[i]);

            if ((itClosed == closedList.end()) && (itOpen == copyOpenList.end()))
            {
                moves[i].setCameFrom(u);
                u.calculateCost(moves[i]);
                this->_openList.push(moves[i]);
                copyOpenList.insert(moves[i]);
            }

            else if (u.getCost() + 1 < moves[i].getCost())
            {
                if (itOpen == copyOpenList.end())
                {
                    this->_openList.push(moves[i]);
                    copyOpenList.insert(moves[i]);
                }

                moves[i].setCameFrom(u);
                u.calculateCost(moves[i]);
            }
        }
    }

    if (!(u == goal))
        throw "Unsolveable";
    Solution<T> sol;
    State<T> tmpState;
    tmpState = u;

    while (!(tmpState == start))
    {
        sol.insertState(tmpState);
        tmpState = tmpState.getCameFrom();
    }

    sol.insertState(tmpState);
    return sol;
}
