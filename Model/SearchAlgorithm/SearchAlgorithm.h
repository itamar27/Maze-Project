#pragma once
#include <queue>
#include <vector>
#include <set>

#include "Searchable.h"
#include "State.h"
#include "Solution.h"
#include "../Maze2d/MazeSearchable.h"

/*
 * --------------------------------------------------------------------
 *		Class: SearchAlgorithm
 *		Description: This class is a generic abstract interface for any kind of search algorithm
 * --------------------------------------------------------------------
 */

template <class T>
class SearchAlgorithm
{
public:
	SearchAlgorithm() {}
	~SearchAlgorithm() {}

public:
	virtual Solution<T> solve(Searchable<T> *s) = 0;
	virtual int getNumOfEvaluatedNodes() = 0;
};

/*
 * --------------------------------------------------------------------
 *		Class: CommonSearcher
 *		Description: This class is generic abstract for common search algorithm of some sort
 *					 implemnting the popList method and returing number of nodes evaluated 
 * --------------------------------------------------------------------
 */

template <class T>
class CommonSearcher : public SearchAlgorithm<T>
{

public:
	CommonSearcher() : _evaluatedNodes(0) {}
	~CommonSearcher(){};

public:
	virtual Solution<T> solve(Searchable<T> *s) = 0;
	
	virtual int getNumOfEvaluatedNodes() { return _evaluatedNodes; };

public:
	const State<T> popList()
	{
		_evaluatedNodes++;
		State<T> tmp = _openList.top();
		_openList.pop();
		return tmp;
	}

protected:
	int _evaluatedNodes;
	std::priority_queue<State<T>, std::vector<State<T>>, std::greater<State<T>>> _openList;
};

