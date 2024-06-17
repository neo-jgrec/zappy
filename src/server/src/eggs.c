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
    egg->x = width == 0 ? 0 : rand() % width;
    egg->y = height == 0 ? 0 :  rand() % height;
    return egg;
}
