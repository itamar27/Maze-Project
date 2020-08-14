#include "SearchAlgorithm.h"

template <class T>
Solution<T> BFS<T>::solve(Searchable<T> *s)
{
    Solution<T> sol;
    std::vector<State<T>> moves;
    State<T> goal = s->getGoalState();
    _openList.push(s->getStartState());

    while (!_openList.empty())
    {
        State<T> u = popList();
        if (u == goal)
            break;
        moves = s->getAllPossibleStates(u);
        
        for(State<T> move : moves)
        {
            
        }
        
    }

    return sol;
}