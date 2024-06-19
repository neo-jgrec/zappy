/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left.c
*/

#include "server.h"

void left(client_t *client, server_t *server)
{
    (void)server;
    switch (client->orientation) {
        case NORTH:
            client->orientation = WEST;
            break;
        case WEST:
            client->orientation = SOUTH;
            break;
        case SOUTH:
            client->orientation = EAST;
            break;
        case EAST:
            client->orientation = NORTH;
            break;
    }
    client->payload = strdup("ok\n");
    message_to_graphicals(server, "ppo %d %d %d %d\n",
        client->fd, client->x, client->y, client->orientation);
    client_time_handler(client, LEFT);
}
