/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** free.c
*/

#include <stdlib.h>

void secure_free(void *elem)
{
    if (elem == NULL)
        return;
    free(elem);
}
