/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** helper.c
*/

#include "server.h"

int helper(char **av, int status)
{
    if (av[1] && (strcmp("-help", av[1]) == 0 || strcmp("-h", av[1]) == 0)) {
        printf("USAGE: ./zappy_server -p port -x width -y ");
        printf("height -n name1 name2 ... -c clientsNb -f freq\n");
    }
    return status;
}
