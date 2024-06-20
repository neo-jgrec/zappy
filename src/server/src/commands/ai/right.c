/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** right.c
*/

#include "server.h"

static const struct {
    int current_orientation;
    int next_orientation;
} next_orientation_table[] = {
    {NORTH, EAST},
    {EAST, SOUTH},
    {SOUTH, WEST},
    {WEST, NORTH},
};

void right(client_t *c, server_t *server)
{
    for (int i = 0; i < 4; i++) {
        if (next_orientation_table[i].current_orientation == c->orientation) {
            c->orientation = next_orientation_table[i].next_orientation;
            break;
        }
    }
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "ppo %d %d %d %d\n",
                            c->fd, c->x, c->y, c->orientation);
        handle_response(&c->payload, "ok\n");
    } else {
        handle_response(&c->payload, "ko\n");
    }
    client_time_handler(c, RIGHT);
}
