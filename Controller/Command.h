#pragma once
#include <iostream>

#include "../Model/Model.h"
class Command
{
public:
    virtual void execute() = 0;
};

/*
 *  Demo Run Command
 */

class DemoRun : public Command
{
public:
    DemoRun(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        _md->runDemo();
    }

private:
    MyModel *_md;
};

/*
 *  ShowDir Command
 */

class ShowDir : public Command
{
public:
    virtual void execute()
    {
        std::cout << "ShowDir Command" << std::endl;
    }
};

/*
 *  Display Maze Command
 */

class DisplayMaze : public Command
{
public:
    DisplayMaze(MyModel *md) : _md(md) {}
    virtual void execute()
    {
        _md->displayMaze();
    }

private:
    MyModel *_md;
};

/*
 *  Generate Maze Command
 */

class GenerateMaze : public Command
{
public:
    GenerateMaze(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        _md->generateMaze();
    }

private:
    MyModel *_md;
};

/*
 *  Save maze Command
 */

class SaveMaze : public Command
{
public:
    SaveMaze(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        std::cout << "SaveMaze Command" << std::endl;
    }

private:
    MyModel *_md;
};

/*
 *  Load maze Command
 */

class LoadMaze : public Command
{
public:
    LoadMaze(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        std::cout << "LoadMaze Command" << std::endl;
    }

private:
    MyModel *_md;
};

/*
 *  Maze Size Command
 */

class MazeSize : public Command
{
public:
    MazeSize(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        std::cout << "MazeSize Command" << std::endl;
    }

private:
    MyModel *_md;
};

/*
 *  File Size Command
 */

class FileSize : public Command
{
public:
    virtual void execute()
    {
        std::cout << "FileSize Command" << std::endl;
    }
};

/*
 *  Solve Maze Command
 */

class SolveMaze : public Command
{
public:
    SolveMaze(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        _md->solve();
    }

private:
    MyModel *_md;
};

/*
 *  Display solution Command
 */

class DisplaySolution : public Command
{
public:
    DisplaySolution(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        _md->displaySolution();
    }

private:
    MyModel *_md;
};

/*
 *  Exit Command
 */

class Exit : public Command
{
public:
    virtual void execute()
    {
        std::cout << "exit Command" << std::endl;
    }
};
