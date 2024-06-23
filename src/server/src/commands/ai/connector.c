/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connector.c
*/

#include "server.h"

static void end_assign_egg_to_client(
    client_t *client,
    server_t *server,
    eggs_list_t *item
)
{
    message_to_graphicals(server, "edi %d\n", client->egg_id);
    handle_response(&client->payload, "ok\n");
    secure_free((void **)&item->egg);
    secure_free((void **)&item);
}

static void asign_egg_to_client(
    client_t *client,
    server_t *server,
    size_t rand_idx
)
{
    size_t counter = 0;
    team_t *team = get_team_by_name(&server->teams, client->commands[0]);

    for (eggs_list_t *item = TAILQ_FIRST(&team->eggs);
        item;
        item = TAILQ_NEXT(item, entries)) {
        if (!(counter == rand_idx)) {
            counter++;
            continue;
        }
        client->is_connected = true;
        client->x = item->egg->x;
        client->y = item->egg->y;
        asprintf(&client->team_name, "%s", team->name);
        clock_gettime(CLOCK_REALTIME, &client->live_time);
        client->egg_id = team->nb_eggs;
        TAILQ_REMOVE(&team->eggs, item, entries);
        end_assign_egg_to_client(client, server, item);
        break;
    }
}

static void print_eggs(client_t *c, server_t *s)
{
    team_t *t;
    egg_t *e;

    for (team_list_t *item_t = TAILQ_FIRST(&s->teams);
        item_t;
        item_t = TAILQ_NEXT(item_t, entries)) {
        t = item_t->team;
        for (eggs_list_t *item_e = TAILQ_FIRST(&t->eggs);
            item_e;
            item_e = TAILQ_NEXT(item_e, entries)) {
            e = item_e->egg;
            dprintf(c->fd, "enw %d %d %d %d\n", e->id, -1, e->x, e->y);
        }
    }
}

static void print_teams(client_t *c, server_t *s)
{
    team_list_t *item;
    team_t *t;

    TAILQ_FOREACH(item, &s->teams, entries) {
        t = item->team;
        dprintf(c->fd, "tna %s\n", t->name);
    }
}

static info_map_t get_tile(server_t *server, size_t x, size_t y)
{
    tile_t tile = server->map[x + y * server->proprieties.width];
    info_map_t info = {0};

    for (size_t i = 0; i < tile.num_objects; i++) {
        info.food += tile.objects[i] == FOOD;
        info.linemate += tile.objects[i] == LINEMATE;
        info.deraumere += tile.objects[i] == DERAUMERE;
        info.sibur += tile.objects[i] == SIBUR;
        info.mendiane += tile.objects[i] == MENDIANE;
        info.phiras += tile.objects[i] == PHIRAS;
        info.thystame += tile.objects[i] == THYSTAME;
    }
    return info;
}

static void print_map_to_gui(client_t *c, server_t *s)
{
    info_map_t info;

    for (int y = 0; y < s->proprieties.height; y++) {
        for (int x = 0; x < s->proprieties.width; x++) {
            info = get_tile(s, x, y);
            dprintf(c->fd, "bct %d %d %d %d %d %d %d %d %d\n",
                x, y, info.food, info.linemate, info.deraumere, info.sibur,
                info.mendiane, info.phiras, info.thystame);
        }
    }
}

static void send_players(client_t *c, server_t *s)
{
    client_list_t *item;
    client_t *tmp;

    TAILQ_FOREACH(item, &s->clients, entries) {
        tmp = item->client;
        if (tmp->is_connected == true && tmp->is_graphic == false) {
            dprintf(c->fd, "pnw %d %u %u %u %zu %s\n", tmp->id, tmp->x,
                tmp->y, tmp->orientation, tmp->level, tmp->team_name);
            dprintf(c->fd, "pin %d %u %u %u %u %u %u %u %u %u\n", tmp->id,
                tmp->x, tmp->y, tmp->inventory.food,
                tmp->inventory.linemate, tmp->inventory.deraumere,
                tmp->inventory.sibur, tmp->inventory.mendiane,
                tmp->inventory.phiras, tmp->inventory.thystame);
        }
    }
}

static void send_everything(client_t *c, server_t *server)
{
    dprintf(c->fd, "msz %u %u\n", server->proprieties.width,
        server->proprieties.height);
    dprintf(c->fd, "sgt %u\n", server->proprieties.frequency);
    print_teams(c, server);
    print_map_to_gui(c, server);
    send_players(c, server);
    print_eggs(c, server);
}

bool connector(client_t *c, server_t *server)
{
    size_t nb_slots;

    if (c->is_connected == true)
        return false;
    if (strcmp(c->commands[0], "GRAPHIC") == 0) {
        c->is_graphic = true;
        c->is_connected = true;
        send_everything(c, server);
        return true;
    }
    nb_slots = team_nb_slots(&server->teams, c->commands[0]);
    if (nb_slots == 0)
        return false;
    asign_egg_to_client(c, server, rand() % nb_slots);
    dprintf(c->fd, "%zu\n%u %u\n", (nb_slots - 1),
        server->proprieties.width, server->proprieties.height);
    message_to_graphicals(server, "pnw %d %u %u %u %u %s\n", c->id, c->x,
        c->y, c->orientation, c->level, c->team_name);
    return true;
}
