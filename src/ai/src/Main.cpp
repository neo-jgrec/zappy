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
    if (ac != 4)
    {
        displayHelp();
        return 84;
    }
    std::string host = av[3];
    int port = std::stoi(av[1]);
    std::string teamName = av[2];

    Client client(host, teamName, port);
    client.run();

    return 0;
}

// to verify: makeThemSegfault: parse message ennemie, if there is a number, change number to 9999999999 to make them segfault