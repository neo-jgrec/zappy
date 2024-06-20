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
            clock_gettime(CLOCK_REALTIME, &client->live_time);
            client->egg_id = team->nb_eggs;
            TAILQ_REMOVE(&team->eggs, item, entries);
            message_to_graphicals(server, "edi %d\n", item->egg->id);
            asprintf(&client->team_name, "%s", client->commands[0]);
            secure_free(item->egg);
            secure_free(item);
            break;
        }
        counter++;
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
        return true;
    }
    nb_slots = team_nb_slots(&server->teams, c->commands[0]);
    if (nb_slots == 0)
        return false;
    rand_idx = rand() % nb_slots;
    asign_egg_to_client(c, server, rand_idx);
    dprintf(c->fd, "%zu\n%u %u\n", (nb_slots - 1),
        server->proprieties.width, server->proprieties.height);
    message_to_graphicals(server, "pnw %d %u %u %u %u %s\n", c->fd, c->fd,
        c->x, c->y, c->orientation, c->team_name);
    return true;
}
