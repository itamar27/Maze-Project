#include "Demo.h"

void Demo::run()
{
    //Creating a Maze and printing it to console
    MyMaze2dGenerator mg;
    Maze2d m2d = mg.generate("Barak", 30, 35);
    std::cout << m2d;

    //Solving the Maze with A* and BFS
    MazeSearchable ms(m2d);
    ManahattanDistance h;
    Astar<Position> aManhattan(&h);
    AriealDistance h2;
    Astar<Position> aArieal(&h2);

    Solution<Position> solA;
    Solution<Position> solBFS;

    BFS<Position> bfs;
    try
    {
        solA = bfs.solve(&ms);

        solBFS = aManhattan.solve(&ms);
        //aArieal.solve(&ms);
    }
    catch (const char *e)
    {
        std::cout << e << std::endl;
    }

    //std::cout << "A* with areial distance Number of nodes eval: " << aArieal.getNumOfEvaluatedNodes() << std::endl;

    std::cout << "A* with manhattan Number of nodes eval: " << aManhattan.getNumOfEvaluatedNodes() << "\n";
    std::cout << "Path size to Solution: " << solA.getSolutionSize() << "\n"
              << solA << std::endl;
    std::cout << "\nBFS Number of nodes eval: " << bfs.getNumOfEvaluatedNodes() << "\n";
    std::cout << "Path size to Solution: " << solBFS.getSolutionSize() << "\n"
              << solBFS << std::endl;
}