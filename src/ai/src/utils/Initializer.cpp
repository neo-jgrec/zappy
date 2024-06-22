/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** Initializer
*/

#include "Initializer.hpp"

Initializer::Initializer()
{
    port = 0;
    teamName = "";
    host = "";
    debug = false;
}

Initializer::~Initializer()
{
}

void Initializer::parseArguments(int ac, char **av)
{

    if (ac != 8 && ac != 7)
    {
        displayHelp();
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];

        if (arg == "-help")
        {
            displayHelp();
            exit(SUCCESS);
        }
        else if (arg == "-p" && i + 1 < ac)
        {
            port = std::stoi(av[++i]);
        }
        else if (arg == "-n" && i + 1 < ac)
        {
            teamName = av[++i];
        }
        else if (arg == "-h" && i + 1 < ac)
        {
            host = av[++i];
        }

        else
        {
            throw InitializerException("Invalid argument: " + arg);
        }
    }

    if (port == 0 || teamName.empty() || host.empty())
    {
        throw InitializerException("Missing required arguments");
    }
}
