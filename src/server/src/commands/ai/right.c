/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right.c
*/

#include "server.h"

void right(client_t *client, server_t *server)
{
    int width = server->proprieties.width;
    int height = server->proprieties.height;
    int direction = client->orientation % 4;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};

    client->orientation = (client->orientation + 1) % 4;
    client->x = (client->x + dx[direction] + width) % width;
    client->y = (client->y + dy[direction] + height) % height;
    client->payload = strdup("ok\n");
    message_to_graphicals(server, "ppo %d %d %d %d\n",
        client->fd, client->x, client->y, client->orientation);
    client_time_handler(client, RIGHT);
}
