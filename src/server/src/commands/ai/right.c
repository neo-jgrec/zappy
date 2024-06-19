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
    if (client->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "ppo %d %d %d %d\n",
        client->fd, client->x, client->y, client->orientation);
        asprintf(&client->payload, "ok\n");
    } else
        asprintf(&client->payload, "ko\n");
    client_time_handler(client, RIGHT);
}
