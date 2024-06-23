/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** eject.c
*/

#include "client.h"
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

static int get_orientation_to_tile(int x, int y, int x2, int y2)
{
    if (x == x2 && y == y2 - 1)
        return NORTH;
    if (x == x2 && y == y2 + 1)
        return SOUTH;
    if (x == x2 - 1 && y == y2)
        return WEST;
    if (x == x2 + 1 && y == y2)
        return EAST;
    return -1;
}

static int set_dx(unsigned char orientation)
{
    if (orientation == WEST)
        return -1;
    if (orientation == EAST)
        return 1;
    return 0;
}

static int set_dy(unsigned char orientation)
{
    if (orientation == NORTH)
        return -1;
    if (orientation == SOUTH)
        return 1;
    return 0;
}

void send_data_to_graphiscs(server_t *s, client_list_t *n)
{
    message_to_graphicals(s, "pex %d\n", n->client->id);
    message_to_graphicals(s, "ppo %d %d %d %d\n", n->client->id,
        n->client->x, n->client->y, n->client->orientation);
}

void eject(client_t *c, server_t *s)
{
    int width = s->proprieties.width;
    int height = s->proprieties.height;
    signed char dx = set_dx(c->orientation);
    signed char dy = set_dy(c->orientation);

    for (client_list_t *n = TAILQ_FIRST(&s->clients); n != NULL;
        n = TAILQ_NEXT(n, entries)) {
        if (n->client->x == c->x && n->client->y == c->y
        && n->client->id != c->id) {
            n->client->x = (n->client->x + dx + width) % width;
            n->client->y = (n->client->y + dy + height) % height;
            dprintf(n->client->fd, "eject: %d\n", get_orientation_to_tile(
                c->x, c->y, n->client->x, n->client->y));
            send_data_to_graphiscs(s, n);
        }
    }
    delete_eggs_on_tile(s, c->x, c->y);
    handle_response(&c->payload, "ok\n");
    client_time_handler(c, EJECT);
}
