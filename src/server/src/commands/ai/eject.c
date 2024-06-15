/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject.c
*/

#include "server.h"

static int reverse_direction(int direction)
{
    switch (direction) {
        case NORTH:
            return SOUTH;
        case SOUTH:
            return NORTH;
        case WEST:
            return EAST;
        case EAST:
            return WEST;
        default:
            return -1;
    }
}

void eject(client_t *c, server_t *s)
{
    unsigned char orientation = c->orientation;
    signed char dx = 0;
    signed char dy = 0;
    client_list_t *node;
    client_t *other_client;
    signed char new_x;
    signed char new_y;

    if (orientation == NORTH)
        dy = -1;
    if (orientation == SOUTH)
        dy = 1;
    if (orientation == WEST)
        dx = -1;
    if (orientation == EAST)
        dx = 1;
    TAILQ_FOREACH(node, &s->clients, entries) {
        other_client = node->client;
        if (other_client->x == c->x && other_client->y == c->y && other_client != c) {
            new_x = (c->x + dx + s->proprieties.width) % s->proprieties.width;
            new_y = (c->y + dy + s->proprieties.height) % s->proprieties.height;
            other_client->x = new_x;
            other_client->y = new_y;
            asprintf(&other_client->payload, "eject: %d\n", reverse_direction(orientation));
        }
    }
    asprintf(&c->payload, "ok\n");
    client_time_handler(c, EJECT);
}
