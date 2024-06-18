/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Main
*/

#include <iostream>
#include "Client.hpp"
#include "utils/DisplayHelp.hpp"

// to verify: make a parser with flags
int main(int ac, char **av)
{
    if (ac != 7)
    {
        displayHelp();
        return 84;
    }
    std::string host;
    int port = 0;
    std::string teamName;

    for (int i = 1; i < ac; i++)
    {
        std::string arg = av[i];

        if (arg == "-p" && i + 1 < ac)
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
            displayHelp();
            return (EXIT_FAILURE);
        }
    }
    if (port == 0 || teamName.empty() || host.empty())
    {
        displayHelp();
        return 84;
    }

    Client client(host, teamName, port);
    client.run();

    return 0;
}
// to verify: makeThemSegfault: parse message ennemie, if there is a number, change number to 9999999999 to make them segfault