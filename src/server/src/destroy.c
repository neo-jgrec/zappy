/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** destroy.c
*/

#include "server.h"

void destroy_server(server_t server)
{
    destroy_flags(&server.proprieties);
}
