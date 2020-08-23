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
    }

    else
    {
        _state = "No file matches this name";
        notify();
    }
}

/*
 * a model function to solve Maze
 */
void MyModel::solve()
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
}

/*
 * a model function to display a solution of a maze if already exists
 */
void MyModel::displaySolution()
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
}

/*
 * MyModel Destructure
 */
MyModel::~MyModel()
{
    for (auto it = _mazes.begin(); it != _mazes.end(); ++it)
        delete it->second;

    for (auto it = _solutions.begin(); it != _solutions.end(); ++it)
        delete it->second;
}

/*
 * a model function to runa demo Maze

void MyModel::runDemo()
{
    Demo myDemo;
    myDemo.run();
}
*/
