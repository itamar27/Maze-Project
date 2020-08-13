#include "./Maze2d.h"
#include "Searchable.h"

/*
 * --------------------------------------------------------------------
 *       Class: MazeSearchAble
 *		 Description: This class is a structural design pattern - Adapter, between Maze2d and Searchable
 * --------------------------------------------------------------------
 */

template <class T>
class MazeSearchable : public Searchable<T>, public Maze2d
{
public:
    MazeSearchable(Maze2d &m2d) : _m2d(m2d) {}
    ~MazeSearchable();

public:
    virtual State<T>& getStartState() {_m2d.getStartPosition();}
    virtual State<T>& getGoalState() {_m2d.getGoalPosition();}
    virtual State<T>& getAllPossibleStates(State<T>& s);

private:
    Maze2d _m2d;
};
