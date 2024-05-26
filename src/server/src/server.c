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

    if (!init_flags(&flags, args)) {
        destroy_flags(&flags);
        return helper(ERROR_STATUS);
    }
    destroy_flags(&flags);
    return OK_STATUS;
}
