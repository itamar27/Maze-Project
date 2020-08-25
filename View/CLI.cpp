#include "CLI.h"

/*
 *      Method: Start()
 *      Description: This method of CLI is the entire interface for user to work with maze 
 */

void CLI::start()
{

    std::string command = "";
    MyController *controller = new MyController(this);
    std::vector<std::string> parameters;
    while (command.compare("exit") != 0)
    {
        _out << ">>";
        std::getline(_in, command);

        parameters = parseInput(command, controller);
        Command *com = controller->get(command);

        if (nullptr != com)
        {
            try
            {
                com->execute(parameters);
            }
            catch (const char *e)
            {
                std::cout << e << std::endl;
            }
        }
        else
            _out << "Unsupported Command!" << std::endl;
    }
    delete controller;
}

/*
 *      Method: getOstream()
 *      Description: A friend function to return the 'out' stream of view to help other MVC members 
 */

std::ostream &CLI::getOStream()
{
    return _out;
}

/* 
 *      Method: parseInput()
 *      Description: This method is parsing the string into a command and a vector that includes 
 */

std::vector<std::string> CLI::parseInput(std::string &str, MyController *con)
{
    std::vector<std::string> vec;
    std::string command = "";
    std::string strCopy = str;
    std::string delimiter = " ";
    size_t pos = 0;

    while (strCopy.length() > 0) // loop for parsing the string into vector where each element is a single word.
    {
        pos = strCopy.find(delimiter);
        vec.push_back(strCopy.substr(0, pos));
        if (pos != std::string::npos)
            strCopy.erase(0, pos + delimiter.length());

        else
            strCopy.erase(0, pos);
    }

    std::string commandCopy = "";
    int commandParse = 0;
    for (int i = 0; i < vec.size(); ++i) // loop for finding the largest command in string
    {
        commandCopy += vec[i];
        if (con->get(commandCopy))
        {
            command = commandCopy;
            commandParse = i + 1;
        }
        commandCopy += " ";
    }

    vec.erase(vec.begin(), (vec.begin() + commandParse));

    str = command;
    return vec;
}
