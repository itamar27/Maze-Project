#pragma once
#include <string>
#include <map>

#include "Command.h"
#include "Observer.h"
#include "../Model/Model.h"
#include "../View/View.h"

/* 
 * ----------------------------------------------------------------------------------
 *      Class: Controller
 *      Description: This class is the interface for the controller part in MVC
 *                   for those who to implement a controller.
 * ----------------------------------------------------------------------------------
 */
class Controller : public Observer
{
public:
    virtual Command *get(const std::string &command) = 0;
};


/* 
 * ----------------------------------------------------------------------------------
 *      Class: MyController
 *      Description: This class is the implementation of the controller interface
 *                    using a pointer to command to work with  low dependncy between command and controller
 * ----------------------------------------------------------------------------------
 */
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