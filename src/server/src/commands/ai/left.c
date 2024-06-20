/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** left.c
*/

#include "server.h"

static const struct {
    int orientation;
    int new_orientation;
} orientation[] = {
    {NORTH, WEST},
    {WEST, SOUTH},
    {SOUTH, EAST},
    {EAST, NORTH}
};

void left(client_t *c, server_t *server)
{
    for (int i = 0; i < 4; i++) {
        if (orientation[i].orientation == c->orientation) {
            c->orientation = orientation[i].new_orientation;
            break;
        }
    }
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "ppo %d %d %d %d\n",
        c->fd, c->x, c->y, c->orientation);
        handle_response(&c->payload, "ok\n");
    } else
        handle_response(&c->payload, "ko\n");
    client_time_handler(c, LEFT);
}
