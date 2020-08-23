#pragma once
#include <vector>
#include <string>

#include "../Controller/Observer.h"

/*
 * --------------------------------------------------------------------
 *       Class:  Observable
 *		 Description: This class is an interface for all enteties that needs to be watch to
 * --------------------------------------------------------------------
 */

class Observable
{
public:
    void Attach(Observer &obs)
    {
        _observers.push_back(&obs);
    }

    void notify()
    {
        for (auto it = _observers.begin(); it != _observers.end(); ++it)
        {
            (*it)->update((*this));
        }
    }

    std::string getState()
    {
        return _state;
    }
    
protected:
    std::vector<Observer *> _observers;
    std::string _state;
};