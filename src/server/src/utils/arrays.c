/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** arrays.c
*/

#include <stdio.h>

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
