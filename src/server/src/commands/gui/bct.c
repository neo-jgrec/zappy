/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** bct.c
*/

#include "server.h"

void bct(client_t *client, server_t *server)
{
    if (client->commands[1] == NULL || client->commands[2] == NULL) {
        message_to_graphicals(server, "sbp\n");
        return;
    }
    (void)server;
}
