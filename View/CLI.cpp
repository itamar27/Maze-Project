#include "CLI.h"

void CLI::start()
{
    std::string command = "";
    MyController *controller = new MyController();

    while (command.compare("exit") != 0)
    {
        _out << ">>";
        std::getline(_in, command);

        Command *com = controller->get(command);

        if (nullptr != com)
        {
            com->execute();
        }
        else
            _out << "Unsupported Command!" << std::endl;
    }
}