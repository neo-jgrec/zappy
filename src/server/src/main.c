/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#include "server.h"

int main(int ac, char **av)
{
    if (ac < 13)
        return helper(ERROR_STATUS);
    return server(av);
}
