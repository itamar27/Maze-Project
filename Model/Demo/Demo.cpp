#include "Demo.h"


/* 
 *      Method: run
 *      Description: This method is methods that makes all the demo's actio
 */

void Demo::run()
{
    //Creating a Maze and printing it to console
    MyMaze2dGenerator mg;
    Maze2d m2d = mg.generate("Demo-Maze");
    std::cout << m2d;

    //Solving the Maze with A* and BFS
    MazeSearchable ms(m2d);
    ManhattanDistance h;
    Astar<Position> aManhattan(&h);
    AriealDistance h2;
    Astar<Position> aArieal(&h2);

    Solution<Position> solAmanhattan;
    Solution<Position> solAarieal;

    Solution<Position> solBFS;

    BFS<Position> bfs;

    try
    {
        solAmanhattan = bfs.solve(&ms);
        solBFS = aManhattan.solve(&ms);
        solAarieal = aArieal.solve(&ms);
    }
    catch (const char *e)
    {
        std::cout << e << std::endl;
    }

    std::cout << "BFS solution evaluated " << bfs.getNumOfEvaluatedNodes() << " states, built a solution path of " << solBFS.getSolutionSize() << ", and it is:" << std::endl;
    std::cout << solBFS << std::endl;
    std::cout << "\nAstar with manhattan solution evaluated " << aManhattan.getNumOfEvaluatedNodes() << " states, built a solution path of " << solBFS.getSolutionSize() << ", and it is:" << std::endl;
    std::cout << solAmanhattan << std::endl;
    std::cout << "\nAstar with Arieal Distance solution evaluated " << aArieal.getNumOfEvaluatedNodes() << " states, built a solution path of " << solBFS.getSolutionSize() << ", and it is:" << std::endl;
    std::cout << solAarieal << std::endl;
}