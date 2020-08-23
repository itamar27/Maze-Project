#pragma once

class Observable;

/*
 * --------------------------------------------------------------------
 *       Class:  Observer
 *		 Description: This class is an interface for observer in observer design pattern.
 * --------------------------------------------------------------------
 */

class Observer
{
public:
    virtual void update(Observable &o) = 0;
};
