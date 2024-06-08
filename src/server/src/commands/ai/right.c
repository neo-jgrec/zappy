/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right.c
*/

#include "server.h"

void right(client_t *client, server_t *server)
{
    (void)server;
    switch (client->orientation) {
        case NORTH:
            client->orientation = EAST;
            break;
        case EAST:
            client->orientation = SOUTH;
            break;
        case SOUTH:
            client->orientation = WEST;
            break;
        case WEST:
            client->orientation = NORTH;
            break;
    }
}
