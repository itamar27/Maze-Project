#pragma once



/*
 * --------------------------------------------------------------------
 *      Class:  View
 *      Description: class that is an interface for all View in MVC.
 * --------------------------------------------------------------------
 */
class View
{
public:
    virtual void start() = 0;
    virtual std::ostream &getOStream() = 0;
};