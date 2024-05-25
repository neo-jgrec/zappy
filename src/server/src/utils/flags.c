/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** flags.c
*/

#include "server.h"

static bool count_flags(size_t flags[NB_FLAGS])
{
    for (size_t i = 0; i < NB_FLAGS; i++) {
        if (flags[i] != 1) {
            return false;
        }
    }
    return true;
}

bool check_number_flags(char **args)
{
    size_t flags[NB_FLAGS] = {0};

    if (!args)
        return false;

    for (size_t i = 0; args[i]; i++) {
        if (strlen(args[i]) != 2)
            continue;
        switch (args[i][1]) {
            case 'p': flags[PORT] += 1; break;
            case 'x': flags[WIDTH] += 1; break;
            case 'y': flags[HEIGHT] += 1; break;
            case 'n': flags[NAME] += 1; break;
            case 'c': flags[CLIENT_NB] += 1; break;
            case 'f': flags[FREQ] += 1; break;
        }
    }
    return count_flags(flags);
}
