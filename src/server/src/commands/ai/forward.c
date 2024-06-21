/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward.c
*/

#include "server.h"

void forward(client_t *c, server_t *server)
{
    int width = server->proprieties.width;
    int height = server->proprieties.height;
    int direction = c->orientation % 4;
    int dx[] = {0, 0, -1, 1};
    int dy[] = {-1, 1, 0, 0};

    c->x = (c->x + dx[direction] + width) % width;
    c->y = (c->y + dy[direction] + height) % height;
    if (c->x < 0)
        c->x += width;
    if (c->y < 0)
        c->y += height;
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "ppo %d %d %d %d\n",
        c->id, c->x, c->y, c->orientation);
        c->payload = strdup("ok\n");
    } else
        c->payload = strdup("ko\n");
    client_time_handler(c, FORWARD);
}
