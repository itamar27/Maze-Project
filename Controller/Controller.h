#pragma once
#include <string>
#include <map>

#include "Command.h"
#include "../Model/Model.h"

class Controller
{
public:
};

class MyController : public Controller
{
public:
    MyController()
    {
        _model = new MyModel();
        _commands["demo"] = new DemoRun(_model);
        _commands["display"] = new DisplayMaze(_model);
        _commands["dir"] = new ShowDir();
        _commands["generate maze"] = new GenerateMaze(_model);
        _commands["save maze"] = new SaveMaze(_model);
        _commands["load maze"] = new LoadMaze(_model);
        _commands["maze size"] = new MazeSize(_model);
        _commands["file size"] = new FileSize();
        _commands["size"] = new MazeSize(_model);
        _commands["solve"] = new SolveMaze(_model);
        _commands["display solution"] = new DisplaySolution(_model);
        _commands["exit"] = new Exit();
    }

    Command *get(const std::string &command)
    {
        auto it = _commands.find(command);
        if (it == _commands.end())
            return nullptr;

        return it->second;
    }

    ~MyController()
    {
        for (auto it = _commands.begin(); it != _commands.end(); ++it)
        {
            delete it->second;
        }

        delete _model;
    }

private:
    std::map<std::string, Command *> _commands;
    MyModel *_model;
};