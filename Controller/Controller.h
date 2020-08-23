#pragma once
#include <string>
#include <map>

#include "Command.h"
#include "Observer.h"
#include "../Model/Model.h"
#include "../View/View.h"

class Controller : public Observer
{
};

class MyController : public Controller
{
public:
    /*
     * To intiazlize a MyController instance we must first use a view (some program interface)
     * to let our user control eveything, the user will chose his in and out streaming channels
     * and will use the view start method to work with our Controller and model parts.
     */
    virtual void update(Observable &o);
    MyController(View *view)
    {
        if (view != nullptr)
            _view = view;

        _model = new MyModel();

        _commands["dir"] = new ShowDir();
        _commands["generate maze"] = new GenerateMaze(_model, _view);
        _commands["display"] = new DisplayMaze(_model, _view);
        _commands["save maze"] = new SaveMaze(_model, _view);
        _commands["load maze"] = new LoadMaze(_model, _view);
        _commands["maze size"] = new MazeSize(_model, _view);
        _commands["file size"] = new FileSize(_model, _view);
        _commands["size"] = new MazeSize(_model, _view);
        _commands["solve"] = new SolveMaze(_model, _view);
        _commands["display solution"] = new DisplaySolution(_model, _view);
        _commands["exit"] = new Exit();
        _commands["demo"] = new DemoRun(_model);
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
    View *_view;
};