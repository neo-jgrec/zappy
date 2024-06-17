/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sgt.c
*/

#include "server.h"

void sgt(client_t *client, server_t *server)
{
    dprintf(client->fd, "sgt %d\n", server->proprieties.frequency);
}
