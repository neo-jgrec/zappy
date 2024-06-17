/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** plv.c
*/

#include "server.h"

void plv(client_t *client, server_t *server)
{
    if (client->commands[1] == NULL) {
        message_to_graphicals(server, "sbp\n");
        return;
    }
    (void)server;
}
