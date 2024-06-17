/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** msz.c
*/

#include "server.h"

void msz(client_t *client, server_t *server)
{
    dprintf(client->fd, "msz %d %d\n",
        server->proprieties.width,
        server->proprieties.height
    );
}
