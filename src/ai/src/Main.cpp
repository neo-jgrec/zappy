/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Main
*/

#include <iostream>
#include "client/Client.hpp"
#include "utils/Initializer.hpp"

int main(int ac, char **av)
{

    Initializer initializer;

    try
    {
        initializer.parseArguments(ac, av);
    }
    catch (Initializer::InitializerException &e)
    {
        PRINT_ERROR(e.what());
        return FAILURE;
    }
    Client client(initializer.host, initializer.teamName, initializer.port);

    client.run();

    return 0;
}
