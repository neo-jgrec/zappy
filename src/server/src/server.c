/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server.c
*/

#include "server.h"

int server(char **args)
{
    if (!check_number_flags(args))
        return ERROR_STATUS;
    return OK_STATUS;
}
