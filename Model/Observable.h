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
    // Add a new observer to the list of this observable member
    void Attach(Observer &obs)
    {
        _observers.push_back(&obs);
    }

    // Notify all observers whom are on mailing list
    void notify()
    {
        for (auto it = _observers.begin(); it != _observers.end(); ++it)
        {
            (*it)->update((*this));
        }
    }

    // return the state (represented by a string) of the observable member
    std::string getState()
    {
        return _state;
    }
    
protected:
    std::vector<Observer *> _observers;
    std::string _state;
};