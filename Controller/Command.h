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
    virtual void execute(std::string s)
    {
        _view->getOStream() << _md->getMaze(s);
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
    GenerateMaze(MyModel *md, View *view) : _md(md) {}

    virtual void execute(std::string s)
    {
        _md->generateMaze(s);
    }

private:
    MyModel *_md;
    View *_view;
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
    SaveMaze(MyModel *md, View *view) : _md(md) {}

    virtual void execute(std::string s)
    {
        std::string name, filename;
        std::string delimiter = " ";
        auto pos = s.find(delimiter);
        name = s.substr(0, pos);
        s.erase(0, pos + delimiter.length());

        _md->saveMaze(name, filename);
    }

private:
    MyModel *_md;
    View *_view;
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
    LoadMaze(MyModel *md, View *view) : _md(md) {}

    virtual void execute(std::string s)
    {
        std::cout << "LoadMaze Command" << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
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
    MazeSize(MyModel *md, View *view) : _md(md) {}

    virtual void execute(std::string s)
    {
        std::cout << "MazeSize Command" << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
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
    virtual void execute(std::string s)
    {
        std::cout << "FileSize Command" << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
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
    SolveMaze(MyModel *md, View *view) : _md(md) {}

    virtual void execute(std::string s)
    {
        _md->solve(s);
    }

private:
    MyModel *_md;
    View *_view;
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
    DisplaySolution(MyModel *md, View *view) : _md(md) {}

    virtual void execute()
    {
        _md->displaySolution(s);
    }

private:
    MyModel *_md;
    View *_view;
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
 * --------------------------------------------------------------------
 *       Class:  DemoRun
 *		 Description: runs a demo program for mazes.
 * --------------------------------------------------------------------
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