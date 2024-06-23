/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation.c
*/

#include "server.h"

static const size_t required_resources[7][7] = {
    {1, 1, 0, 0, 0, 0, 0},
    {2, 1, 1, 1, 0, 0, 0},
    {2, 2, 0, 1, 0, 2, 0},
    {4, 1, 1, 2, 0, 1, 0},
    {4, 1, 2, 1, 3, 0, 0},
    {6, 1, 2, 3, 0, 1, 0},
    {6, 2, 2, 2, 2, 2, 1}
};

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

static bool check_requirements_met(
    const info_map_t resource_count,
    size_t players_on_tile,
    size_t required_level
)
{
    const size_t* req = required_resources[required_level - 1];
    return (
        players_on_tile >= req[0] &&
        resource_count.linemate >= req[1] &&
        resource_count.deraumere >= req[2] &&
        resource_count.sibur >= req[3] &&
        resource_count.mendiane >= req[4] &&
        resource_count.phiras >= req[5] &&
        resource_count.thystame >= req[6]
    );
}


static void remove_resource_from_tile(
    tile_t *tile,
    size_t resource_type,
    size_t *resource_count
)
{
    for (size_t j = 0; j < tile->num_objects; j++) {
        if (tile->objects[j] == resource_type) {
            tile->objects[j] = tile->objects[tile->num_objects - 1];
            resource_count[resource_type]--;
            break;
        }
    }
}

static void remove_resources(tile_t *tile, info_map_t resources, size_t required_level)
{
    size_t resource_count[7] = {
        resources.food,
        resources.linemate,
        resources.deraumere,
        resources.sibur,
        resources.mendiane,
        resources.phiras,
        resources.thystame
    };

    for (size_t i = 0; i < 7; i++) {
        for (size_t j = 0; j < required_resources[required_level - 1][i]; j++) {
            remove_resource_from_tile(tile, i, resource_count);
        }
    }
}

static size_t get_nb_players_on_tile(client_t *client, server_t *server)
{
    size_t players_on_tile = 0;
    client_list_t *client_entry = NULL;

    if (client == NULL || TAILQ_EMPTY(&server->clients))
        return 0;
    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client
            && client_entry->client->is_graphic == false
            && client_entry->client->x == client->x
            && client_entry->client->y == client->y
            && client_entry->client->level == client->level)
            players_on_tile++;
    }
    return players_on_tile;
}

static void run_logic_on_group(
    client_t *client,
    server_t *server,
    size_t required_level,
    void (*func)(client_t *client, server_t *server)
)
{
    client_list_t *client_entry = NULL;

    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client
            && client_entry->client->is_graphic == false
            && client_entry->client->x == client->x
            && client_entry->client->y == client->y
            && client_entry->client->level == required_level)
            func(client_entry->client, server);
    }
}

static bool are_requierment_met_encapsulation(
    client_t *client,
    info_map_t resource_count,
    size_t players_on_tile,
    size_t required_level
)
{
    if (!check_requirements_met(
        resource_count,
        players_on_tile,
        required_level)
    ) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    return true;
}

void incantation(client_t *client, server_t *server)
{
    info_map_t resource_count = get_tile(server, client->x, client->y);
    size_t players_on_tile = get_nb_players_on_tile(client, server);

    if (!are_requierment_met_encapsulation(client, resource_count,
        players_on_tile, client->level))
        return;
    run_logic_on_group(client, server, client->level, callback_freeze);
    run_logic_on_group(client, server, client->level,
        callback_start_incantation_set_payload);
    send_start_incantation_to_graphicals(client, server);
    client_time_handler(client, INCANTATION);
}

void incantation_callback_end_of_command(client_t *c, server_t *s)
{
    info_map_t resource_count = get_tile(s, c->x, c->y);
    size_t players_on_tile = get_nb_players_on_tile(c, s);
    tile_t *tile = &s->map[c->x + c->y * s->proprieties.width];

    if (!are_requierment_met_encapsulation(c, resource_count,
        players_on_tile, c->level)) {
        run_logic_on_group(c, s, c->level, callback_unfreeze);
        message_to_graphicals(s, "pie %hhd %hhd %d\n", c->x, c->y, 0);
        return;
    }
    remove_resources(tile, resource_count, c->level);
    run_logic_on_group(c, s, c->level, callback_level_up);
    run_logic_on_group(c, s, c->level,
        callback_end_incantation_set_payload);
    message_to_graphicals(s, "pie %hhd %hhd %d\n", c->x, c->y, 1);
    if (c->level == LAST_LEVEL)
        message_to_graphicals(s, "seg %s\n", c->team_name);
}
