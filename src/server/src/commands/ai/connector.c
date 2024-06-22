/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connector.c
*/

#include "server.h"

static void asign_egg_to_client(
    client_t *client,
    server_t *server,
    size_t rand_idx
)
{
    eggs_list_t *item;
    size_t counter = 0;
    team_t *team = get_team_by_name(&server->teams, client->commands[0]);

    TAILQ_FOREACH(item, &team->eggs, entries) {
        if (counter == rand_idx) {
            client->is_connected = true;
            client->x = item->egg->x;
            client->y = item->egg->y;
            asprintf(&client->team_name, "%s", team->name);
            clock_gettime(CLOCK_REALTIME, &client->live_time);
            client->egg_id = team->nb_eggs;
            TAILQ_REMOVE(&team->eggs, item, entries);
            message_to_graphicals(server, "edi %d\n", item->egg->id);
            handle_response(&client->payload, "ok\n");
            secure_free((void**)&item->egg);
            secure_free((void**)&item);
            break;
        }
        counter++;
    }
}

static void print_eggs(server_t *s)
{
    team_list_t *item_t;
    eggs_list_t *item_e;
    team_t *t;
    egg_t *e;

    TAILQ_FOREACH(item_t, &s->teams, entries) {
        t = item_t->team;
        TAILQ_FOREACH(item_e, &t->eggs, entries) {
            e = item_e->egg;
            message_to_graphicals(s, "enw %d %d %d %d\n", e->id, -1, e->x, e->y);
        }
    }
}

bool connector(client_t *c, server_t *server)
{
    size_t nb_slots;
    size_t rand_idx;

    if (c->is_connected == true)
        return false;
    if (strcmp(c->commands[0], "GRAPHIC") == 0) {
        c->is_graphic = true;
        c->is_connected = true;
        print_eggs(server);
        return true;
    }
    nb_slots = team_nb_slots(&server->teams, c->commands[0]);
    if (nb_slots == 0)
        return false;
    rand_idx = rand() % nb_slots;
    asign_egg_to_client(c, server, rand_idx);
    dprintf(c->fd, "%zu\n%u %u\n", (nb_slots - 1),
        server->proprieties.width, server->proprieties.height);
    message_to_graphicals(server, "pnw %d %u %u %u %u %s\n", c->id, c->x,
        c->y, c->orientation, c->level, c->team_name);
    return true;
}
