#pragma once
#include <iostream>
#include <string>

#include "View.h"

class CLI : public View
{

public:
    CLI() : _out(std::cout), _in(std::cin){};
    CLI(std::ostream &out, std::istream &in) : _out(out), _in(in) {}
    ~CLI() {}

public:
    virtual void start() const;

private:
    std::ostream& _out;
    std::istream& _in;
};
