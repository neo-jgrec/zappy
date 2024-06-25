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
    int direction = c->orientation;
    int dx[] = {0, 1, 0, -1};
    int dy[] = {-1, 0, 1, 0};
    static int forward = 0;

    c->x = (c->x + dx[direction - 1] + width) % width;
    c->y = (c->y + dy[direction - 1] + height) % height;
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
    printf("forward: %d\n", forward);
    printf("client->x: %d\n", c->x);
    printf("client->y: %d\n", c->y);
    printf("client->orientation: %s\n", c->orientation == NORTH ? "NORTH" : c->orientation == EAST ? "EAST" : c->orientation == SOUTH ? "SOUTH" : "WEST");
    forward++;
}
