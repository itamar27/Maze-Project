#include "Maze2d/Maze2dGenerator.h"
#include "SearchAlgorithm/SearchAlgorithm.h"
#include "SearchAlgorithm/Searchable.h"
#include "SearchAlgorithm/State.h"
#include "Maze2d/Position.h"

int main()
{
    /*SimpleMaze2dGenerator genMaze2;
    std::string name2 = "Barak2";
    std::string time2 = genMaze2.measureAlgorithmTime(name2, 30, 30);
    Maze2d m2d2 = genMaze2.generate(name2, 30, 30);
    std::cout << "Time to create maze: " << time2  << m2d2<< "\n";

    MyMaze2dGenerator genMaze;
    std::string name = "Barak";
    std::string time = genMaze.measureAlgorithmTime(name, 30, 30);
    Maze2d m2d = genMaze.generate(name, 50, 50);
    std::cout << "Time to create maze: " << time << m2d << "\n";
    */

    // MyMaze2dGenerator myMaze;
    // std::cout << "Time to run " << myMaze.measureAlgorithmTime("Barak", 40, 40) << std::endl;

    // Maze2d maze = myMaze.generate("Barka", 40, 40);

    // Position p = maze.getGoalPosition();
    // std::cout << "goal: " << p << std::endl;
    
    // std::string* moves = maze.getPossibleMoves(p);  

    // std::cout<<"Possible move is: "<<std::endl;
    // for(int i = 0; i < 4; i++)
    // {   
    //     if(moves[i] == "" )
    //         continue;
    //     else
    //     {
    //         std::cout<< moves[i]<<std::endl;
    //     }        
    // }

    // std::cout<<"entrance: " << maze.getStartPosition()<<std::endl;

    // std::cout<< maze<<std::endl;
    
}
