#include <iostream>

#include "./View/CLI.h"
#include "./Controller/Controller.h"
#include "./Model/Model.h"

int main()
{

    CLI * myCli = new CLI(std::cout, std::cin);

    myCli->start();
}


 