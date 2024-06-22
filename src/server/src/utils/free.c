/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** free.c
*/

#include <stdlib.h>

void secure_free(void **ptr)
{
    if (ptr != NULL && *ptr != NULL) {
        free(*ptr);
        *ptr = NULL;
    }
}
