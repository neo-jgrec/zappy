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
        case NORTH:
            client->y -= 1;
            break;
        case SOUTH:
            client->y += 1;
            break;
        case WEST:
            client->x -= 1;
            break;
        case EAST:
            client->x += 1;
            break;
    }
    client->y = (client->y >= server->proprieties.height) ? 0 : client->y;
    client->y = (client->y < 0) ? server->proprieties.height - 1 : client->y;
    client->x = (client->x >= server->proprieties.width) ? 0 : client->x;
    client->x = (client->x < 0) ? server->proprieties.width - 1 : client->x;
    client->payload = strdup("ok\n");
    message_to_graphicals(server, "ppo %d %d %d %d\n",
        client->fd, client->x, client->y, client->orientation);
    client_time_handler(client, FORWARD);
}
