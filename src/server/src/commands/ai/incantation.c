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

static bool check_incantation_requirements(client_t *client, server_t *server, const size_t *required_resources)
{
    tile_t *tile = &server->map[client->x + client->y * server->proprieties.width];
    size_t players_on_tile = 0;
    size_t resource_count[8] = {0};

    client_list_t *client_entry;
    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client->x == client->x && client_entry->client->y == client->y) {
            if (client_entry->client->level == client->level && client_entry->client->uuid != client->uuid) {
                players_on_tile++;
            }
        }
    }

    for (size_t i = 0; i < tile->num_objects; i++) {
        switch (tile->objects[i]) {
            case LINEMATE: resource_count[LINEMATE]++; break;
            case DERAUMERE: resource_count[DERAUMERE]++; break;
            case SIBUR: resource_count[SIBUR]++; break;
            case MENDIANE: resource_count[MENDIANE]++; break;
            case PHIRAS: resource_count[PHIRAS]++; break;
            case THYSTAME: resource_count[THYSTAME]++; break;
            default: break;
        }
    }

    printf("resource_count: %ld %ld %ld %ld %ld %ld %ld\n", resource_count[1], resource_count[2], resource_count[3], resource_count[4], resource_count[5], resource_count[6], resource_count[7]);

    for (size_t i = 1; i < 7; i++) {
        if (resource_count[i] < required_resources[i]) {
            printf("resource_count[i]: %ld\n", resource_count[i]);
            return false;
        }
    }

    printf("players_on_tile: %ld\n", players_on_tile);

    if (players_on_tile < required_resources[0]) {
        return false;
    }

    return true;
}

static void remove_resources_from_tile(tile_t *tile, const size_t *required_resources)
{
    size_t resource_count[8] = {0};

    for (size_t i = 0; i < tile->num_objects; i++) {
        switch (tile->objects[i]) {
            case LINEMATE: resource_count[LINEMATE]++; break;
            case DERAUMERE: resource_count[DERAUMERE]++; break;
            case SIBUR: resource_count[SIBUR]++; break;
            case MENDIANE: resource_count[MENDIANE]++; break;
            case PHIRAS: resource_count[PHIRAS]++; break;
            case THYSTAME: resource_count[THYSTAME]++; break;
            default: break;
        }
    }

    for (size_t i = 1; i < 7; i++) {
        while (resource_count[i] > required_resources[i]) {
            for (size_t j = 0; j < tile->num_objects; j++) {
                if (tile->objects[j] == i) {
                    tile->objects[j] = tile->objects[--tile->num_objects];
                    resource_count[i]--;
                    break;
                }
            }
        }
    }
}

void incantation(client_t *client, server_t *server)
{

    size_t original_level = client->level;

    if (!check_incantation_requirements(client, server, required_resources[client->level - 1])) {
        (void)asprintf(&client->payload, "ko\n");
        return;
    }

    client_list_t *client_entry;
    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client->x == client->x && client_entry->client->y == client->y) {
            if (client_entry->client->level == original_level) {
                for (int i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
                    client_entry->client->tclient[i].available_request = false;
                }
            }
        }
    }

    client_time_handler(client, INCANTATION);

    if (!check_incantation_requirements(client, server, required_resources[client->level - 1])) {
        (void)asprintf(&client->payload, "ko\n");
        return;
    }

    client_entry = NULL;
    TAILQ_FOREACH(client_entry, &server->clients, entries) {
        if (client_entry->client->x == client->x && client_entry->client->y == client->y) {
            if (client_entry->client->level == original_level) {
                client_entry->client->level++;
                for (int i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
                    client_entry->client->tclient[i].available_request = true;
                }
            }
        }
    }

    remove_resources_from_tile(
        &server->map[client->x + client->y * server->proprieties.width],
        required_resources[client->level - 1]
    );

    (void)asprintf(&client->payload, "elevation en cours\n");
}
