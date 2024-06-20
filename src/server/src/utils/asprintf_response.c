/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** client.c
*/

#include "client.h"
#include <stdarg.h>

void handle_response(char **dest, const char *fmt, ...)
{
    va_list args;
    char *response = NULL;

    va_start(args, fmt);
    if (vasprintf(&response, fmt, args) != -1) {
        *dest = response;
    }
    va_end(args);
}
