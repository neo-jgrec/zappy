/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pin.c
*/

#include "server.h"

void pin(client_t *client, server_t *server)
{
    if (client->commands[1] == NULL) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    (void)server;
}
