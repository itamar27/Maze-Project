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
    MyController(View *view);
    ~MyController();
    
public:
    Command *get(const std::string &command);
    virtual void update(Observable &o);

private:
    std::map<std::string, Command *> _commands;
    MyModel *_model;
    View *_view;
};