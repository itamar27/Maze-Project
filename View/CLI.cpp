#include "CLI.h"

/*
 * This method of CLI is the entire interface for user to work with maze 
 */

void CLI::start()
{
    std::string command = "";
    MyController *controller = new MyController(this);

    while (command.compare("exit") != 0)
    {
        _out << ">>";
        std::getline(_in, command);

        Command *com = controller->get(command);

        if (nullptr != com)
            com->execute();

        else
            _out << "Unsupported Command!" << std::endl;
    }
}

/*
 * A friend function to print into view out member 
 */

std::ostream &CLI::getOStream()
{
    return _out;
}
