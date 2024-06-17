/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sst.c
*/

#include "server.h"

void sst(client_t *client, server_t *server)
{
    if (!client->commands[1]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    server->proprieties.frequency = atoi(client->commands[1]);
    if (server->proprieties.frequency < 1) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    dprintf(client->fd, "sst %d\n", server->proprieties.frequency);
}
