/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** str_utils.c
*/

#include <stdbool.h>
#include <stdio.h>

bool str_is_num(const char *str)
{
    for (size_t i = 0; str[i]; i++) {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}
