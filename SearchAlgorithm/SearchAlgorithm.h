#pragma once
#include <queue>

#include "Searchable.h"


/*
 * --------------------------------------------------------------------
 *       Class: SearchAlgorithm
 *		 Description: This class is a generic abstract interface for any kind of search algorithm
 * --------------------------------------------------------------------
 */

template <class T>
class SearchAlgorithm
{
public:
	virtual void solve(const Searchable<T> &s) = 0;
	virtual int getNumOfEvaluatedNodes() = 0;
};


/*
 * --------------------------------------------------------------------
 *       Class: CommonSearcher
 *		 Description: This class is generic abstract for common search algorithm of some sort
 *					  implemnting the popList method and returing number of nodes evaluated 
 * --------------------------------------------------------------------
 */

template <class T>
class CommonSearcher : public SearchAlgorithm
{
public:
	virtual int getNumOfEvaluatedNodes(){return };

public:
	const State<T>& popList(){_evaluatedNodes ++; return _openList.pop();}

private:
	int _evaluatedNodes;
	std::priority_queue<State<T>> _openList;
};


/*
 * --------------------------------------------------------------------
 *       Class: BFS
 *		 Description: This class implements a generic BFS algorithm for any kind of searcherable class
 * --------------------------------------------------------------------
 */
template <class T>
class BFS : public CommonSearcher
{
public:
	virtual void solve(const Searchable<T>& s;
};


/*
 * --------------------------------------------------------------------
 *       Class: A*
 *		 Description: This class implements a generic A* algorithm for any kind of searcherable class
 * --------------------------------------------------------------------
 */template <class T>
class Astar : public CommonSearcher
{
public:
};