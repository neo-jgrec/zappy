/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eggs.c
*/

#include "server.h"

egg_t *init_egg(int width, int height)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (egg == NULL)
        return NULL;
    egg->x = rand() % width;
    egg->y = rand() % height;
    return egg;
}
