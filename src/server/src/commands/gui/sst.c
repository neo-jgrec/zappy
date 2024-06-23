/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sst.c
*/

#include "server.h"

void sst(client_t *client, server_t *server)
{
    int freq;

    if (!client->commands[1]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    freq = atoi(client->commands[1]);
    if (freq < 1) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    server->proprieties.frequency = freq;
    dprintf(client->fd, "sst %d\n", server->proprieties.frequency);
}
