#pragma once
#include <map>

#include "./Maze2d/Position.h"
#include "./Maze2d/Maze2d.h"
#include "./SearchAlgorithm/Solution.h"
#include "Demo/Demo.h"

class Model
{
public:
    virtual void generateMaze() = 0;
    virtual void displayMaze() = 0;
    virtual void saveMaze() = 0;
    virtual void loadMaze() = 0;
    virtual void getMazeSize() = 0;
    virtual void solve() = 0;
    virtual void displaySolution() = 0;
    virtual void getFileSize() = 0;
    virtual void runDemo() = 0;

private:
};

class MyModel : public Model
{
public:
    virtual void generateMaze()
    {
        std::string s;
        std::cout << "Please enter a maze name: " << std::endl;
        std::getline(std::cin, s);
        MyMaze2dGenerator m2dg;
        Maze2d *m2d = new Maze2d(m2dg.generate(s, 20, 20));
        _mazes[s] = m2d;
        _solutions[m2d] = nullptr;
    };

    virtual void displayMaze()
    {
        std::string s;
        std::cout << "Please enter a maze name: " << std::endl;
        std::getline(std::cin, s);

        auto it = _mazes.find(s);
        if (it == _mazes.end())
            std::cout << "No such maze exists" << std::endl;
        else
            std::cout << *(it->second) << std::endl;
    };

    virtual void saveMaze(){};
    virtual void loadMaze(){};
    virtual void getMazeSize(){};

    virtual void solve()
    {
        std::string s;
        std::cout << "Please enter a maze name: " << std::endl;
        std::getline(std::cin, s);
        auto mazeIt = _mazes.find(s);
        auto solIt = _solutions.find(mazeIt->second);

        if (mazeIt == _mazes.end())
        {
            std::cout << "No such maze exists" << std::endl;
        }
        else if (solIt->second == nullptr)
        {
            MazeSearchable ms(*(solIt->first));
            ManahattanDistance h;
            Astar<Position> aManhattan(&h);
            Solution<Position> solAmanhattan;

            solAmanhattan = aManhattan.solve(&ms);
            solIt->second = new Solution<Position>(solAmanhattan);
        }
        else
            std::cout << "This maze was already solved" << std::endl;
    };

    virtual void displaySolution()
    {
        std::string s;
        std::cout << "Please enter a maze name: " << std::endl;
        std::getline(std::cin, s);
        auto mazeIt = _mazes.find(s);
        auto solIt = _solutions.find(mazeIt->second);
        if (mazeIt == _mazes.end())
        {
            std::cout << "No such maze exists" << std::endl;
        }
        else if (solIt->second != nullptr)
        {
            std::cout << *(solIt->second) << std::endl;
        }
        else
            std::cout << "This maze was hasn't been solved yet" << std::endl;
    };
    virtual void getFileSize(){};
    virtual void runDemo()
    {
        Demo myDemo;
        myDemo.run();
    };

    ~MyModel()
    {
        for (auto it = _solutions.begin(); it != _solutions.end(); ++it)
        {
            delete it->second;
            delete it->first;
        }
    }

private:
    std::map<Maze2d *, Solution<Position> *> _solutions;
    std::map<std::string, Maze2d *> _mazes;
};