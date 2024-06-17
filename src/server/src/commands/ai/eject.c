/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject.c
*/

#include "server.h"

static int reverse_orientation(int direction)
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

static void set_dx_and_dy(
    unsigned char orientation,
    signed char *dx,
    signed char *dy
)
{
    if (orientation == NORTH)
        *dy = -1;
    if (orientation == SOUTH)
        *dy = 1;
    if (orientation == WEST)
        *dx = -1;
    if (orientation == EAST)
        *dx = 1;
}

static void send_player_expulsion_to_graphicals(
    server_t *s,
    client_t *c
)
{
    client_list_t *n;

    TAILQ_FOREACH(n, &s->clients, entries) {
        if (n->client->is_graphic)
            dprintf(n->client->fd, "pex %d\n", c->fd);
    }
}

void eject(client_t *c, server_t *s)
{
    signed char dx = 0;
    signed char dy = 0;
    client_list_t *n;
    signed char new_x;
    signed char new_y;

    set_dx_and_dy(c->orientation, &dx, &dy);
    TAILQ_FOREACH(n, &s->clients, entries) {
        if (n->client->x == c->x && n->client->y == c->y && n->client != c) {
            new_x = (c->x + dx + s->proprieties.width) % s->proprieties.width;
            new_y = (c->y + dy + s->proprieties.height)
                % s->proprieties.height;
            n->client->x = new_x;
            n->client->y = new_y;
            asprintf(&n->client->payload,
                "eject: %d\n", reverse_orientation(c->orientation));
            send_player_expulsion_to_graphicals(s, n->client);
        }
    }
    asprintf(&c->payload, "ok\n");
    client_time_handler(c, EJECT);
}
