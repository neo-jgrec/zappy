/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward.c
*/

#include "server.h"

void forward(client_t *client, server_t *server)
{
    switch (client->orientation) {
        case NORTH: client->y -= 1;
            break;
        case SOUTH: client->y += 1;
            break;
        case WEST: client->x -= 1;
            break;
        case EAST: client->x += 1;
            break;
    }
    if (client->y >= server->proprieties.height)
        client->y = 0;
    if (client->y < 0)
        client->y = (signed char)server->proprieties.height - 1;
    if (client->x >= server->proprieties.width)
        client->x = 0;
    if (client->x < 0)
        client->x = (signed char)server->proprieties.width - 1;
}
