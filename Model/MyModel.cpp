#include "Model.h"

/*
 *      Method: generateMaze()
 *      Description: A model function to generate maze
 */
void MyModel::generateMaze(std::string s, int len, int width)
{
    MyMaze2dGenerator m2dg;
    Maze2d *m2d = new Maze2d(m2dg.generate(s, len, width));
    _mazes[s] = m2d;

    // Observer pattern usage
    _state = "Maze is generated";
    notify();
}
/*
 *      Method: getMaze()
 *      Description: a model function to return a maze that can be displayed
 */
Maze2d *MyModel::getMaze(std::string name)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
        return nullptr;
    }

    else
    {
        return (it->second);
    }
}

/*
 *      Method: saveMaze() 
 *      Description: a model function to save Maze and his solution
 */

void MyModel::saveMaze(std::string name, std::ofstream *oFile)
{
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
    }

    else
    {
        if (oFile != NULL)
        {
            auto itsol = _solutions.find(name);
            if (itsol != _solutions.end())
            {
                itsol->second->write(*oFile);
            }
            else
            {
                int zero = 0;
                oFile->write((char *)&zero, sizeof(int));
            }

            MazeCompression comp;
            comp.write(*oFile, *(it->second));

            _state = "Maze was saved";
            notify();
        }
        else
        {
            _state = "Error opening this file";
            notify();
        }
    }
}

/*
 *      Method: loadMaze() 
 *      Description: a model function to load Maze
 */

void MyModel::loadMaze(std::ifstream *iFile, std::string name)
{
    if (iFile != NULL)
    {
        MazeCompression m2d;
        Solution<Position> sol;
        int size;

        iFile->read((char *)&size, sizeof(size));

        if (size != 0)
        {
            iFile->seekg(0, std::ios::beg);
            sol.read(*iFile);
            _solutions[name] = new Solution<Position>(sol);
        }
        if (name != "")
        {
            _mazes[name] = new Maze2d(m2d.read(*iFile));
            _mazes[name]->setName(name);
        }
        else
        {
            Maze2d *m2dTmp = new Maze2d(m2d.read(*iFile));
            _mazes[m2dTmp->getMazeName()] = m2dTmp;
        }
    }

    else
    {
        _state = "No file matches this name";
        notify();
    }
}

/*
 *      Method: getMazeSize() 
 *      Description: a model function to return the Maze size
 */

int MyModel::getMazeSize(std::string name)
{
    int size = 0;
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
        return size;
    }

    size = sizeof(*(it->second));
    return size;
}

/*
 *      Method: getFileSize() 
 *      Description: a model function to return the Maze size
 */
int MyModel::getFileSize(std::string name)
{
    int size = 0;
    auto it = _mazes.find(name);
    if (it == _mazes.end())
    {
        _state = "Maze " + name + " Not exists";
        notify();
        return size;
    }

    MazeCompression comp;
    size += it->second->getMazeName().length();
    size += sizeof(it->second->getStartPosition());
    size += sizeof(it->second->getGoalPosition());
    size += comp.compress(it->second->getData()).size() * sizeof(int);
    return size;
}

/*
 *      Method: solve()
 *      Description: a model function to solve Maze
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
 *      Method: displaySolution() 
 *      Description: a model function to display a solution of a maze if already exists
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
 *      Method: runDemo()
 *      Description: a model function to runa demo Maze --> not required on the work details 
 *                   but we decided to add it as functionalty of interface
 */

void MyModel::runDemo()
{
    Demo myDemo;
    myDemo.run();
}


/*
 *      Method: saveAllMazes()
 *      Description: Saves all the mazes in the map and their solutions
 */

void MyModel::saveAllMazes(std::ofstream *saveFile)
{
    for (auto it = _mazes.begin(); it != _mazes.end(); ++it)
    {
        saveMaze(it->first, saveFile);
    }
}

/*
 *      Method: loadAllMazes() 
 *      Description: Load all the mazes in the map and their solutions
 */

void MyModel::loadAllMazes(std::ifstream *loadFile)
{
    for (auto it = _mazes.begin(); it != _mazes.end(); ++it)
    {
        loadMaze(loadFile);
    }
}

/*
 *      Method: ~MyModel() 
 *      Description: MyModel Destructor
 */
MyModel::~MyModel()
{
    for (auto it = _mazes.begin(); it != _mazes.end(); ++it)
        delete it->second;

    for (auto it = _solutions.begin(); it != _solutions.end(); ++it)
        delete it->second;
}