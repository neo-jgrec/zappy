/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** take.c
*/

#include "server.h"

void take(client_t *client, server_t *server)
{
    client_time_handler(client, TAKE);
}
