#include "MazeCompression.h"

/*
 * Function to get a row large 2 dimensions int array and compress it to 1 dimensional array
 */
std::vector<int> MazeCompression::compress(std::vector<std::vector<int>> data)
{

    std::vector<int> compressed;
    int count = 1;
    int j = 0;
    int i = 0;

    int row = data.size();
    int col = data[0].size();

    // This loops iterates through a 2d vector with indices method of 1d vector
    while (i < row - 1 || j < col)
    {
        if ((j == col - 1) && (i < row - 1))
        {
            if (data[i][j] == data[i + 1][0])
                ++count;
            else if (data[i][j] != data[i + 1][0])
            {
                compressed.push_back(data[i][j]);
                compressed.push_back(count);
                count = 1;
            }
            j = 0;
            i++;
        }

        if (data[i][j] != data[i][j + 1])
        {
            compressed.push_back(data[i][j]);
            compressed.push_back(count);
            count = 0;
        }

        ++j;
        ++count;
    }

    return compressed;
}

/*
 * Function to decompress a one 1d vector into a 2d vector
 */

std::vector<std::vector<int>> MazeCompression::decompress(std::vector<int> data, int length, int width)
{
    std::vector<std::vector<int>> decompress(length, std::vector<int>(width, 1));
    int count = 0;
    int token = 1;
    int indx = 1;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (count == 0)
            {
                if (indx < data.size())
                {
                    count = data[indx];
                    token = data[indx - 1];
                    indx += 2;
                }
            }
            decompress[i][j] = token;
            count--;
        }
    }

    return decompress;
}

/*
 * Function to write to a file a compressed maze
 */
void MazeCompression::write(std::ofstream &out, const Maze2d &m2d)
{
    int n = m2d.getMazeName().length();
    const char *name = m2d.getMazeName().c_str();
    int startX = m2d.getStartPosition().getX();
    int startY = m2d.getStartPosition().getY();
    int exitX = m2d.getGoalPosition().getX();
    int exitY = m2d.getGoalPosition().getY();
    int length = m2d.getData().size();
    int width = m2d.getData()[1].size();
    auto vec = compress(m2d.getData());

    out.write((char *)&n, sizeof(n));
    out.write(name, n);
    out.write((char *)&startX, sizeof(startX));
    out.write((char *)&startY, sizeof(startY));
    out.write((char *)&exitX, sizeof(exitX));
    out.write((char *)&exitY, sizeof(exitY));
    out.write((char *)&length, sizeof(length));
    out.write((char *)&width, sizeof(width));

    out.write((char *)&vec[0], vec.size() * sizeof(int));
}

/*
 * Function to load from a file and decompressed maze
 */

Maze2d MazeCompression::read(std::ifstream &in)
{
    int n = 0;
    char *tname;
    int startX = 0;
    int startY = 0;
    int exitX = 0;
    int exitY = 0;
    int length = 0;
    int width = 0;
    std::vector<int> vec;

    in.read((char *)&n, sizeof(n));
    if (n != 0)
    {
        tname = new char[n + 1];
        in.read(tname, n);
        tname[n] = '\0';
    }
    in.read((char *)&startX, sizeof(startX));
    in.read((char *)&startY, sizeof(startY));
    in.read((char *)&exitX, sizeof(exitX));
    in.read((char *)&exitY, sizeof(exitY));
    in.read((char *)&length, sizeof(length));
    in.read((char *)&width, sizeof(width));

    int tmp;
    while (in.read((char *)&tmp, sizeof(tmp)))
    {
        vec.push_back(tmp);
    }

    auto vec2d = decompress(vec, length, width);

    std::string name(tname);
    delete tname;

    return Maze2d(name, Position(startX, startY), Position(exitX, exitY), vec2d);
}
