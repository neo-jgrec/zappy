/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast.c
*/

#include "server.h"

void broadcast(client_t *client, server_t *server)
{
    client_t *clt;

    if (client->commands[1] == NULL)
        return;
    clt = server->clients;
    for (; clt; clt = clt->next) {
        if (client->fd != clt->fd)
            dprintf(clt->fd, "%s\n", client->commands[1]);
    }
}
