/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject.c
*/

#include "server.h"

static void purge_eggs_from_team(team_t *team, int x, int y)
{
    eggs_list_t *egg;

    TAILQ_FOREACH(egg, &team->eggs, entries) {
        if (egg->egg->x == x && egg->egg->y == y) {
            TAILQ_REMOVE(&team->eggs, egg, entries);
            free(egg->egg);
            free(egg);
            team->nb_eggs--;
        }
    }
}

static void delete_eggs_on_tile(server_t *s, int x, int y)
{
    team_list_t *team;

    TAILQ_FOREACH(team, &s->teams, entries)
        purge_eggs_from_team(team->team, x, y);
}

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

void eject(client_t *c, server_t *s)
{
    signed char x = 0;
    signed char y = 0;
    client_list_t *n;
    signed char new_x;
    signed char new_y;

    set_dx_and_dy(c->orientation, &x, &y);
    TAILQ_FOREACH(n, &s->clients, entries) {
        if (n->client->x == c->x && n->client->y == c->y && n->client != c) {
            new_x = (c->x + x + s->proprieties.width) % s->proprieties.width;
            new_y = (c->y + y + s->proprieties.height) % s->proprieties.height;
            n->client->x = new_x;
            n->client->y = new_y;
            asprintf(&n->client->payload,
                    "eject: %d\n", reverse_orientation(c->orientation));
            message_to_graphicals(s, "pex %d\n", n->client->fd);
            message_to_graphicals(s, "ppo %d %d %d %d\n", n->client->fd,
                n->client->x, n->client->y, n->client->orientation);
        }
    }
    delete_eggs_on_tile(s, c->x, c->y);
    asprintf(&c->payload, "ok\n");
    client_time_handler(c, EJECT);
}
