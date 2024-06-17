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

static void count_resources(tile_t *tile, size_t *resource_count)
{
    for (size_t i = 0; i < tile->num_objects; i++)
        resource_count[tile->objects[i]]++;
}

static bool check_requirements_met(
    const size_t *resource_count,
    const size_t *z,
    size_t players_on_tile
)
{
    for (size_t i = 1; i < 7; i++) {
        if (resource_count[i] < z[i]) {
            fprintf(stderr, "Insufficient resources of type %zu\n", i);
            return false;
        }
    }
    if (players_on_tile < z[0]) {
        fprintf(stderr, "Insufficient players on the tile\n");
        return false;
    }
    return true;
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

static void remove_resources(tile_t *tile, const size_t *required_resources)
{
    size_t resource_count[8] = {0};

    count_resources(tile, resource_count);
    for (size_t i = 1; i < 7; i++) {
        while (resource_count[i] > required_resources[i]) {
            remove_resource_from_tile(tile, i, resource_count);
        }
    }
}

static size_t get_nb_players_on_tile(client_t *client, server_t *server)
{
    size_t players_on_tile = 0;
    client_list_t *client_entry;

    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client->x == client->x
            && client_entry->client->y == client->y
            && client_entry->client->level == client->level
            && client_entry->client->uuid != client->uuid)
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
    client_list_t *client_entry;

    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client->x == client->x
            && client_entry->client->y == client->y
            && client_entry->client->level == required_level)
            func(client_entry->client, server);
    }
}

static bool are_requierment_met_encapsulation(
    client_t *client,
    size_t *resource_count,
    size_t players_on_tile,
    size_t required_level
)
{
    if (!check_requirements_met(
        resource_count,
        required_resources[required_level],
        players_on_tile)
    ) {
        dprintf(client->fd, "ko\n");
        return false;
    }
    return true;
}

void incantation(client_t *client, server_t *server)
{
    size_t required_level = client->level - 1;
    size_t resource_count[8] = {0};
    size_t players_on_tile = get_nb_players_on_tile(client, server);
    tile_t *tile = &server
        ->map[client->x + client->y * server->proprieties.width];

    count_resources(tile, resource_count);
    if (!are_requierment_met_encapsulation(client, resource_count,
        players_on_tile, required_level))
        return;
    run_logic_on_group(client, server, required_level, callback_freeze);
    run_logic_on_group(client, server, required_level,
        callback_start_incantation_set_payload);
    send_start_incantation_to_graphicals(client, server);
    client_time_handler(client, INCANTATION);
}

void incantation_callback_end_of_command(client_t *client, server_t *server)
{
    size_t required_level = client->level - 1;
    size_t old_level = client->level;
    size_t resource_count[8] = {0};
    size_t players_on_tile = get_nb_players_on_tile(client, server);
    tile_t *tile = &server
        ->map[client->x + client->y * server->proprieties.width];

    count_resources(tile, resource_count);
    if (!are_requierment_met_encapsulation(client, resource_count,
        players_on_tile, required_level)) {
        run_logic_on_group(client, server, required_level, callback_unfreeze);
        return;
    }
    remove_resources(tile, required_resources[old_level]);
    run_logic_on_group(client, server, old_level, callback_level_up);
    run_logic_on_group(client, server, old_level,
        callback_end_incantation_set_payload);
}
