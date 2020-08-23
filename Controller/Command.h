#pragma once
#include <iostream>

#include "../Model/Model.h"
#include "../View/View.h"

/*
 * --------------------------------------------------------------------
 *       Class:  Command
 *		 Description: class that is being used to implement commands for Controller.
 * --------------------------------------------------------------------
 */
class Command
{
public:
    virtual void execute() = 0;
};

/*
 * --------------------------------------------------------------------
 *       Class:  ShowDir
 *		 Description: Class command to show the path to program.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  DisplayMaze
 *		 Description: Class command to receive a maze from myModel 
                      and print it to out channel of myView
 * --------------------------------------------------------------------
 */

class DisplayMaze : public Command
{
public:
    DisplayMaze(MyModel *md, View *view) : _md(md), _view(view) {}
    virtual void execute()
    {
        std::string name; //still needs to parse that name
        _view->getOStream() << _md->getMaze(name);
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  GenerateMaze
 *		 Description: class command to generate a new maze.
 * --------------------------------------------------------------------
 */

class GenerateMaze : public Command
{
public:
    GenerateMaze(MyModel *md) : _md(md) {}

    virtual void execute()
    {
        std::string name; //Need to parse name of maze
        _md->generateMaze(name);
    }

private:
    MyModel *_md;
};

/*
 * --------------------------------------------------------------------
 *       Class:  SaveMaze
 *		 Description: class command to save compressed maze and if a solution save it as well.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  LoadMaze
 *		 Description: class command that is beign used to load compressed maze and Solution if has one.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  MazeSize
 *		 Description: class Command to display the size of maze [length\height].
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  FileSize
 *		 Description: class command to display the size of file holding mazes or solution.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  SolveMaze
 *		 Description: class command for solving a maze.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  DisplaySolution
 *		 Description: class command to display the solution for solved maze.
 * --------------------------------------------------------------------
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
 * --------------------------------------------------------------------
 *       Class:  Exit
 *		 Description: class command to exit a program.
 * --------------------------------------------------------------------
 */

class Exit : public Command
{
public:
    virtual void execute()
    {
        std::cout << "exit Command" << std::endl;
    }
};

/*
 *  Demo Run Command
 

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
};*/