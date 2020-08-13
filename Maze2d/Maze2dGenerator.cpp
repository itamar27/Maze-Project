#include "Maze2dGenerator.h"

/*
 * This algorithm measure the time it takes to build a 2d maze
 */

std::string Maze2dGeneratorAbstract::measureAlgorithmTime(std::string name,
                                                          const int &width, const int &height)
{
    // Get starting timepoint
    auto start = std::chrono::high_resolution_clock::now().time_since_epoch();

    // Call the function to generate maze
    generate(name, width, height);

    // Get ending timepoint
    auto stop = std::chrono::high_resolution_clock::now().time_since_epoch();

    // Get duration. Substart timepoints to
    // get durarion. To cast it to proper unit
    // use duration cast method

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);

    return std::to_string(duration.count());
}

/*
 * This algorithm build a simple maze based on randomization
 */
Maze2d SimpleMaze2dGenerator::generate(const std::string &name, int length, int width)
{

    // Minimum size of maze is 15x15, check for size and randomly generate new size
    srand(time(NULL));
    if (length < 15 || length > 1000)
        length = (rand() % 1001) + 15;

    if (width < 15 || width > 1000)
        width = (rand() % 1001) + 15;

    // Creating a new maze2d with walls (=1)

    std::vector<std::vector<int>> tmp2d(length, std::vector<int>(width, 1));

    // Start will get random value, 0 for left to right, 1 for top to bottom
    int start = rand() % 2;

    Position entrance;
    Position exit;

    // Depends on start, initializing random number of passaged and their indexes
    if (start == 0)
    {
        int randomIdx = (rand() % (length - 2)) + 1;
        tmp2d[randomIdx][0] = 0;
        entrance.setX(randomIdx);
        entrance.setY(0);
        int lastPassage = randomIdx;

        for (int i = 1; i < width - 1; ++i)
        {
            tmp2d[lastPassage][i] = 0;
            int numOfPassages = rand() % (length - 2);

            while (numOfPassages-- > 0)
            {
                randomIdx = (rand() % (length - 2)) + 1;
                if (randomIdx - 1 == lastPassage || randomIdx + 1 == lastPassage)
                {
                    tmp2d[randomIdx][i] = 0;
                    lastPassage = randomIdx;
                }
            }
        }
        tmp2d[lastPassage][width - 1] = 0;
        exit.setX(lastPassage);
        exit.setY(width - 1);
    }

    // Depends on start, initializing random number of passages and their indexes
    if (start == 1)
    {
        int randomIdx = (rand() % (width - 2)) + 1;
        tmp2d[0][randomIdx] = 0;
        entrance.setX(0);
        entrance.setY(randomIdx);
        int lastPassage = randomIdx;

        for (int i = 1; i < length - 1; ++i)
        {
            tmp2d[i][lastPassage] = 0;
            int numOfPassages = rand() % (width - 2);

            while (numOfPassages-- > 0)
            {
                randomIdx = (rand() % (width - 2)) + 1;
                if (randomIdx - 1 == lastPassage || randomIdx + 1 == lastPassage)
                {
                    tmp2d[i][randomIdx] = 0;
                    lastPassage = randomIdx;
                }
            }
        }
        tmp2d[length - 1][lastPassage] = 0;
        exit.setX(length - 1);
        exit.setY(lastPassage);
    }

    return Maze2d(name, entrance, exit, entrance, tmp2d);
}

/*
 * This algorithm builds a maze , pesudo code from https://en.wikipedia.org/wiki/Maze_generation_algorithm
 */
Maze2d MyMaze2dGenerator::generate(const std::string &name, int length, int width)
{
    std::stack<Position> path;
    Position entrance, exit, tmp;
    std::random_device rd;
    std::mt19937 mt(rd());

    // Minimum size of maze is 15x15, check for size and randomly generate new size
    srand(time(NULL));
    if (length < 15 || length > 1000)
        length = (rand() % 1001) + 15;

    if (width < 15 || width > 1000)
        width = (rand() % 1001) + 15;

    // Intiazliing maze with walls (=1) and neurtal values (=2)
    std::vector<std::vector<int>> tmp2d(length, std::vector<int>(width, 1));

    for (int i = 1; i < length - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            //tmp2d[i][j] = 2;
            tmp2d.at(i).at(j) = 2;
        }
    }

    //Intializing entrance position by a random choice between 4 walls and the opposite direction for for exit
    srand(time(NULL));
    int left = (rand() % 2);
    int top = rand() % 2;
    if (left && top)
    {
        entrance.setX((rand() % (length - 2)) + 1);
        entrance.setY(width - 1);

        exit.setY(0);
        exit.setX((rand() % (length - 2)) + 1);

        tmp.setY(1);
        tmp.setX(exit.getX());
    }

    else if (!left && top)
    {
        entrance.setX((rand() % (length - 2)) + 1);
        entrance.setY(0);

        exit.setY(width - 1);
        exit.setX((rand() % (length - 2)) + 1);

        tmp.setY(width - 2);
        tmp.setX(exit.getX());
    }

    else if (left && !top)
    {
        exit.setX(0);
        exit.setY((rand() % (width - 2)) + 1);

        entrance.setX(length - 1);
        entrance.setY((rand() % (width - 2)) + 1);

        tmp.setY(exit.getY());
        tmp.setX(1);
    }

    else if (!left && !top)
    {
        exit.setX(length - 1);
        exit.setY((rand() % (width - 2)) + 1);

        entrance.setX(0);
        entrance.setY((rand() % (width - 2)) + 1);

        tmp.setY(exit.getY());
        tmp.setX(length - 2);
    }

    tmp2d[exit.getX()][exit.getY()] = 0;
    tmp2d[entrance.getX()][entrance.getY()] = 0;

    path.push(entrance);

    // while stack is not empty create new path in maze
    while (!path.empty())
    {
        srand(time(NULL));
        std::vector<Position> v;
        Position cur = path.top();
        path.pop();
        int x = cur.getX();
        int y = cur.getY();
        if (tmp2d[x][y] == 1)
            continue;

        tmp2d[x][y] = 0;
        // enter all unvisited neighbours of the current position
        if (x > 0) //&& tmp2d[x - 1][y] != 1)
        {
            if (tmp2d[x - 1][y] == 2)
            {
                tmp2d[x - 1][y] = 3;
                v.push_back(Position(x - 1, y));
            }
            else if (tmp2d[x - 1][y] == 3)
                tmp2d[x - 1][y] = 1;
        }

        if (x < length - 1) //&& tmp2d[x + 1][y] != 1)
        {
            if (tmp2d[x + 1][y] == 2)
            {
                tmp2d[x + 1][y] = 3;
                v.push_back(Position(x + 1, y));
            }
            else if (tmp2d[x + 1][y] == 3)
                tmp2d[x + 1][y] = 1;
        }

        if (y > 0) //&& tmp2d[x][y - 1] != 1)
        {

            if (tmp2d[x][y - 1] == 2)
            {
                tmp2d[x][y - 1] = 3;
                v.push_back(Position(x, y - 1));
            }
            else if (tmp2d[x][y - 1] == 3)
                tmp2d[x][y - 1] = 1;
        }

        if (y < width - 1) // && tmp2d[x][y + 1] != 1)
        {
            if (tmp2d[x][y + 1] == 2)
            {
                tmp2d[x][y + 1] = 3;
                v.push_back(Position(x, y + 1));
            }
            else if (tmp2d[x][y + 1] == 3)
                tmp2d[x][y + 1] = 1;
        }

        // push randomly into the stack from the neighbours vector
        while (!v.empty())
        {
            std::uniform_int_distribution<int> dist(0, v.size());
            int rng = dist(mt);
            if (rng == v.size())
                --rng;
            path.push(v.at(rng));
            v.erase(v.begin() + rng);
        }
    }
    //Making sure there is an open path to the exit
    tmp2d[tmp.getX()][tmp.getY()] = 0;

    return Maze2d(name, entrance, exit, entrance, tmp2d);
}