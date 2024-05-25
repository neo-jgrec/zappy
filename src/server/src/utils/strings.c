/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** str_utils.c
*/

#include <stdbool.h>
#include <ctype.h>
#include <stddef.h>

bool str_is_num(const char *str)
{
    for (size_t i = 0; str[i]; i++) {
        if (!isdigit(str[i]))
            return false;
    }
    return true;
}
