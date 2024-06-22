/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** forward.c
*/

#include "server.h"

void forward(client_t *c, server_t *server)
{
    int x = c->x;
    int y = c->y;

    if (c->orientation == NORTH)
        y = (y - 1 + server->proprieties.height) % server->proprieties.height;
    if (c->orientation == SOUTH)
        y = (y + 1) % server->proprieties.height;
    if (c->orientation == EAST)
        x = (x + 1) % server->proprieties.width;
    if (c->orientation == WEST)
        x = (x - 1 + server->proprieties.width) % server->proprieties.width;
    c->x = x;
    c->y = y;
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "ppo %d %d %d %d\n",
        c->id, c->x, c->y, c->orientation);
        c->payload = strdup("ok\n");
    } else
        c->payload = strdup("ko\n");
    client_time_handler(c, FORWARD);
}
