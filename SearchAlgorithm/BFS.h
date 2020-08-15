#pragma once

#include "SearchAlgorithm.h"

/*
 * --------------------------------------------------------------------
 *       Class: BFS
 *		 Description: This class implements a generic BFS algorithm for any kind of searcherable class
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

//----------------------------------------------------------------------------
//-------------------------------------------------------------------------------
template <class T>
Solution<T> BFS<T>::solve(Searchable<T> *s)
{
    if (s == nullptr)
        throw "Not a Valid pointer";

    std::cout << "Inside of bfs function" << std::endl;
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

        // if (closedList.size() > 0)
        // {
        //     std::cout << std::endl
        //               << "Closed list: " << std::endl;
        //     for (auto it = closedList.begin(); it != closedList.end(); it++)
        //     {
        //         State<T> tmp;
        //         tmp = *it;
        //         std::cout << tmp.getState() << " ";
        //     }
        //     std::cout << std::endl;
        // }

        for (int i = 0; i < moves.size(); ++i)
        {
            // std::cout << "\nFather node is: " << u.getState() << std::endl;
            // std::cout << "Possible move[" << i << "]: " << moves[i].getState() << std::endl;

            auto itClosed = closedList.find(moves[i]);
            auto itOpen = copyOpenList.find(moves[i]);

            // if ((itClosed == closedList.end()))
            //     std::cout << "Not in closed List " << std::endl;
            // if ((itOpen == copyOpenList.end()))
            //     std::cout << "Not in open List " << std::endl;
            if ((itClosed == closedList.end()) && (itOpen == copyOpenList.end()))
            {
                moves[i].setCameFrom(u);
                u.calculateCost(moves[i]);
                this->_openList.push(moves[i]);
                copyOpenList.insert(moves[i]);
                //std::cout << "This child goes into 1ST open!" << std::endl;
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
            // std::cout << "open list size: " << copyOpenList.size() << std::endl;
            // std::cout << "Closed list size: " << closedList.size() << std::endl;
        }
    }

    // std::cout << "           " << std::endl;
    // std::cout << u.getState() << std::endl;
    // std::cout << start.getState() << std::endl;
    // std::cout << goal.getState() << std::endl;

    Solution<T> sol;
    State<T>* ptrState;
    ptrState = &u;
    while (!(*ptrState == start))
    {
        sol.insertState(*ptrState);
        ptrState = ptrState->getCameFrom();
        std::cout << "came from: " << ptrState->getState() << std::endl;
    }
    sol.insertState(u);
    ptrState = ptrState->getCameFrom();
    return sol;
}
