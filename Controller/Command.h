#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

#include "../Model/Model.h"
#include "../View/View.h"

#define data_file "last_updated.txt"

/*
 * --------------------------------------------------------------------
 *       Class:  Command
 *		 Description: class that is an interface for commands.
 *                    (Based on command design pattern).
 * --------------------------------------------------------------------
 */
class Command
{
public:
    virtual void execute(std::vector<std::string> param) = 0;
};

/*
 * --------------------------------------------------------------------
 *       Class:  ShowDir
 *		 Description: Command class to show the file listed in some given path
 * --------------------------------------------------------------------
 */

class ShowDir : public Command
{
public:
    ShowDir(MyModel *md, View *view) : _md(md), _view(view) {}

public:
    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() < 1)
        {
            throw "Not a valid number of arguments for 'dir'";
        }

        std::string path = "";
        for (auto it = param.begin(); it != param.end(); ++it)
            path += *it + " ";

        if (auto dir = opendir(path.c_str()))
        {
            while (auto f = readdir(dir))
            {
                if (!f->d_name || f->d_name[0] == '.')
                    continue; // Skip everything that starts with a dot

                _view->getOStream() << f->d_name << " ";
            }
            _view->getOStream() << "\n";
            closedir(dir);
        }
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  DisplayMaze
 *		 Description: Command class to receive a maze from myModel 
 *                    and print it to out channel of myView
 * --------------------------------------------------------------------
 */

class DisplayMaze : public Command
{
public:
    DisplayMaze(MyModel *md, View *view) : _md(md), _view(view) {}

public:
    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 1)
        {
            throw "Not a valid number of arguments";
        }

        auto ptr = _md->getMaze(param[0]);
        if (ptr != nullptr)
            _view->getOStream() << *ptr;
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  GenerateMaze
 *		 Description: Command class to generate a new maze.
 *                    uses the observer pattern to let the user know when maze is ready
 * --------------------------------------------------------------------
 */

class GenerateMaze : public Command
{
public:
    GenerateMaze(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() < 1 || param.size() > 3)
        {
            throw "Not a valid number of arguments";
        }

        if (param.size() > 2)
            _md->generateMaze(param[0], std::stoi(param[1]), std::stoi(param[2]));
        else
            _md->generateMaze(param[0]);
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  SaveMaze
 *		 Description: Command class to save compressed maze and if a solution save it as well.
 * --------------------------------------------------------------------
 */

class SaveMaze : public Command
{
public:
    SaveMaze(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 2)
        {
            throw "Not a valid number of arguments";
        }

        else
        {
            std::ofstream oFile(param[1], std::ios::out | std::ios::binary);
            if (oFile.is_open())
                _md->saveMaze(param[0], &oFile);
            else
                throw "Error with this file";

            oFile.close();
        }
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  LoadMaze
 *		 Description: Command class that is beign used to load compressed maze and Solution if has one.
 * --------------------------------------------------------------------
 */

class LoadMaze : public Command
{
public:
    LoadMaze(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if ((param.size() < 1) || (param.size() > 2))
        {
            throw "Not a valid number of arguments";
        }

        else
        {
            std::ifstream iFile(param[0], std::ios::out | std::ios::binary);
            if (iFile.is_open())
            {
                if (param.size() == 1)
                    _md->loadMaze(&iFile);
                else
                    _md->loadMaze(&iFile, param[1]);
            }
            else
                throw "Error with this file";

            iFile.close();
        }
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  MazeSize
 *		 Description: Command class to display the size of maze [length\height].
 * --------------------------------------------------------------------
 */
class MazeSize : public Command
{
public:
    MazeSize(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 1)
        {
            throw "Not a valid number of arguments";
        }
        int size = _md->getMazeSize(param[0]);

        if (size != 0)
            _view->getOStream() << "Size in bytes: " << size << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
};
/*
 * --------------------------------------------------------------------
 *       Class:  FileSize
 *		 Description: Command class to display the size of file holding mazes or solution.
 * --------------------------------------------------------------------
 */

class FileSize : public Command
{
public:
    FileSize(MyModel *md, View *view) : _md(md), _view(view) {}

public:
    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 1)
        {
            throw "Not a valid number of arguments";
        }
        int size = _md->getFileSize(param[0]);
        if (size != 0)
            _view->getOStream() << "Compressed size in bytes: " << size << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  SolveMaze
 *		 Description: Command class for solving a maze.
 * --------------------------------------------------------------------
 */

class SolveMaze : public Command
{
public:
    SolveMaze(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 2 && param.size() != 3)
        {
            throw "Not a valid number of arguments";
        }

        //concatenating a the vector into string 
        if(param.size() == 3)
            param[1] += " " + param[2];

        _md->solve(param[0], param[1]);
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  DisplaySolution
 *		 Description: Command class to display the solution for solved maze.
 * --------------------------------------------------------------------
 */

class DisplaySolution : public Command
{
public:
    DisplaySolution(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() != 1)
        {
            throw "Not a valid number of arguments";
        }

        _view->getOStream() << _md->displaySolution(param[0]) << std::endl;
    }

private:
    MyModel *_md;
    View *_view;
};

/*
 * --------------------------------------------------------------------
 *       Class:  Exit
 *		 Description: Command class to exit a program, save all cached data before closing.
 * --------------------------------------------------------------------
 */

class Exit : public Command
{
public:
    Exit(MyModel *md, View *view) : _md(md), _view(view) {}

    virtual void execute(std::vector<std::string> param)
    {
        std::ofstream saveFile(data_file, std::ios::out | std::ios::binary);
        _md->saveAllMazes(&saveFile);
        saveFile.close();
    }

private:
    MyModel *_md;
    View *_view;
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

    virtual void execute(std::vector<std::string> param)
    {
        if (param.size() > 1)
        {
            throw "Not a valid number of arguments";
        }
        _md->runDemo();
    }

private:
    MyModel *_md;
};