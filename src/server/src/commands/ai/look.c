/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look.c
*/

#include "server.h"

void look(client_t *client, server_t *server)
{
    client_time_handler(client, LOOK);
}
