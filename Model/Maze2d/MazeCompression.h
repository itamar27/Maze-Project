#pragma once
#include <vector>
#include <fstream>
#include <string>

#include "Maze2d.h"

/*
 * --------------------------------------------------------------------
 *      Class: MazeCompression
 *      Description: This class is used to compress maze2d data, writing to file and read it
 * --------------------------------------------------------------------
 */

class MazeCompression
{
public:
    MazeCompression() {}
    ~MazeCompression() {}

public:
    std::vector<int> compress(std::vector<std::vector<int>> data);
    std::vector<std::vector<int>> decompress(std::vector<int> data, int length, int width);

    void write(std::ofstream &out, const Maze2d &m2d);
    Maze2d read(std::ifstream &in);
};
