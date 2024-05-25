/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server.c
*/

#include "server.h"

int server(char **args)
{
    flags_t flags = {0};

    if (!check_number_flags(args))
        return helper(ERROR_STATUS);
    return OK_STATUS;
}
