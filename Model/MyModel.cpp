#include "Model.h"

/*
 *  A model function to generate maze
 */
void MyModel::generateMaze(std::string s)
{
    MyMaze2dGenerator m2dg;
    Maze2d *m2d = new Maze2d(m2dg.generate(s, 20, 20));
    _mazes[s] = m2d;

    // Observer pattern usage
    _state = "Maze is generated";
    notify();
}

/*
 * a model function to display Maze
 */
Maze2d &MyModel::getMaze(std::string name)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
    }

    else
    {
        return *(it->second);
    }
}

/*
 * a model function to save Maze and his solution
 */

void MyModel::saveMaze(std::string name, std::string filename)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
    }

    else
    {
        std::ofstream oFile(filename.c_str(), std::ios::out | std::ios::binary | std::ios::app);

        if (oFile.is_open())
        {
            auto itsol = _solutions.find(name);
            if (itsol != _solutions.end())
            {
                itsol->second->write(oFile);
            }
            else
            {
                int zero = 0;
                oFile.write((char *)&zero, sizeof(int));
            }

            MazeCompression comp;
            comp.write(oFile, *(it->second));

            _state = "Maze was saved";
            notify();

            oFile.close();
        }
        else
        {
            _state = "Error open this file";
            notify();
        }
    }
}

/*
 * a model function to load Maze
 */

void MyModel::loadMaze(std::string filename, std::string name)
{
    std::ifstream iFile(filename, std::ios::in | std::ios::binary);
    if (iFile.is_open())
    {
        MazeCompression m2d;
        Solution<Position> sol;
        int size;

        iFile.read((char *)&size, sizeof(size));

        if (size != 0)
        {
            iFile.seekg(0, std::ios::beg);
            sol.read(iFile);
            _solutions[name] = new Solution<Position>(sol);
        }

        _mazes[name] = new Maze2d(m2d.read(iFile));
        _mazes[name]->setName(name);

        iFile.close();
    }

    else
    {
        _state = "No file matches this name";
        notify();
    }
}

/*
 * a model function to return the Maze size
 */

int MyModel::getMazeSize(std::string name)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
        return 0;
    }

    return sizeof(*(it->second));
}

/*
 * a model function to return the Maze size
 */
int MyModel::getFileSize(std::string name)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
        return 0;
    }

    MazeCompression comp;
    int size = 0;
    size += it->second->getMazeName().length();
    size += sizeof(it->second->getStartPosition());
    size += sizeof(it->second->getGoalPosition());
    size += comp.compress(it->second->getData()).size() * sizeof(int);

    return size;
}

/*
 * a model function to solve Maze
 */
void MyModel::solve(std::string name, std::string algorithm)
{
    auto it = _mazes.find(name);

    if (it == _mazes.end())
    {
        _state = "No Maze exist with this name";
        notify();
        return;
    }

    auto itsol = _solutions.find(name);

    if (itsol == _solutions.end())
    {
        MazeSearchable ms(*(it->second));
        if ("A*Manhattan" == algorithm)
        {
            ManhattanDistance h;
            Astar<Position> algo(&h);
            itsol->second = new Solution<Position>(algo.solve(&ms));
        }

        if ("A*Arieal" == algorithm)
        {
            AriealDistance h;
            Astar<Position> algo(&h);
            itsol->second = new Solution<Position>(algo.solve(&ms));
        }

        if ("BFS" == algorithm)
        {
            BFS<Position> algo;
            itsol->second = new Solution<Position>(algo.solve(&ms));
        }

        else
        {
            _state = "No algorithm matches your search";
            notify();
            return;
        }
    }

    _state = "Maze '" + name + "' is solved";
    notify();
}

/*
 * a model function to display a solution of a maze if already exists
 */

Solution<Position> MyModel::displaySolution(std::string name)
{
    auto it = _mazes.find(name);
    auto itsol = _solutions.find(name);
    Solution<Position> sol;
    if (it == _mazes.end())
    {
        _state = "No Maze matchs this name";
        notify();
    }

    else if (itsol == _solutions.end())
    {
        _state = "No Solution for this maze";
        notify();
    }
    else
        sol = *(itsol->second);

    return sol;
}

/*
 * a model function to runa demo Maze --> not required on the work details 
 * but we decided to add it as functionalty of interface
 */
void MyModel::runDemo()
{
    Demo myDemo;
    myDemo.run();
}

/*
 * MyModel Destructor
 */
MyModel::~MyModel()
{
    for (auto it = _mazes.begin(); it != _mazes.end(); ++it)
        delete it->second;

    for (auto it = _solutions.begin(); it != _solutions.end(); ++it)
        delete it->second;
}