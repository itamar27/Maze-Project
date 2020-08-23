#pragma once
#include <iostream>
#include <string>

#include "View.h"
#include "../Controller/Controller.h"

/*
 * --------------------------------------------------------------------
 *       Class:  CLI
 *		 Description: class that is being used to implement the View interface.
 * --------------------------------------------------------------------
 */

class CLI : public View
{

public:
    CLI() : _out(std::cout), _in(std::cin){};
    CLI(std::ostream &out, std::istream &in) : _out(out), _in(in) {}
    ~CLI() {}

public:
    virtual void start();
    virtual std::ostream &getOStream();

private:
    std::ostream &_out;
    std::istream &_in;
};
