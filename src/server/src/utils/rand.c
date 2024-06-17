/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** rand.c
*/

#include "server.h"

int rand_p(int val)
{
    return val == 0  ? 0 : rand() % val;
}
