/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** arrays.c
*/

#include "utils.h"

size_t array_len(void **array)
{
    size_t len = 0;

    if (!array)
        return 0;
    for (; array[len]; len++);
    return len;
}

void free_array(void **array)
{
    if (!array)
        return;
    for (size_t i = 0; array[i]; i++)
        secure_free((void**)&array[i]);
    free(array);
    array = NULL;
}

void print_string_array(char **array)
{
    if (array == NULL) {
        printf("Array is NULL\n");
        return;
    }
    for (size_t i = 0; array[i]; i++) {
        printf("%s\n", array[i]);
    }
}
