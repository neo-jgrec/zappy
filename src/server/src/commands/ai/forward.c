/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward.c
*/

#include "server.h"

void forward(client_t *client, server_t *server)
{
    int width = server->proprieties.width;
    int height = server->proprieties.height;
    int direction = client->orientation % 4;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    client->x = (client->x + dx[direction] + width) % width;
    client->y = (client->y + dy[direction] + height) % height;
    if (client->x < 0)
        client->x += width;
    if (client->y < 0)
        client->y += height;
    client->payload = strdup("ok\n");
    message_to_graphicals(server, "ppo %d %d %d %d\n",
        client->fd, client->x, client->y, client->orientation);
    client_time_handler(client, FORWARD);
}
