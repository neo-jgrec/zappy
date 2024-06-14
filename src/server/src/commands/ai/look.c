/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** look.c
*/

#include "server.h"

static const struct {
    object_t type;
    char *name;
} object_handlers[] = {
    {EMPTY, ""},
    {FOOD, "food"},
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
    {PLAYER, "player"},
    {0, NULL}
};

static void populate_map_with_players(tile_t **map, client_t *client, server_t *server)
{
    client_list_t *tmp;
    tile_t tile;

    TAILQ_FOREACH(tmp, &server->clients, entries) {
        tile = map[client->y][client->x];
        tile.num_objects++;
        tile.objects = realloc(tile.objects,
            sizeof(tile.objects) * tile.num_objects);
        tile.objects[tile.num_objects - 1] = PLAYER;
        map[client->y][client->x] = tile;
    }
}

static void check_object_in_lookup_table(client_t *client, object_t object)
{
    int asprintf_retval = 0;

    for (size_t i = 0; object_handlers[i].name != NULL; i++) {
        if (object_handlers[i].type == object) {
            asprintf_retval = asprintf(&client->payload, "%s %s",
                client->payload, object_handlers[i].name);
            break;
        }
    }
    if (asprintf_retval == -1)
        return;
}

static void object_to_string(client_t *client, tile_t tile)
{
    for (size_t i = 0; i < tile.num_objects; i++)
        check_object_in_lookup_table(client, tile.objects[i]);
    if (asprintf(&client->payload, "%s,", client->payload) == -1)
        return;
}

void look(client_t *client, server_t *server)
{
    tile_t **map = malloc(sizeof(tile_t *) * server->proprieties.height);
    tile_t tile;
    client->payload = "[";

    for (int i = 0; i < server->proprieties.height; i++) {
        map[i] = malloc(sizeof(tile_t) * server->proprieties.width);
        for (int j = 0; j < server->proprieties.width; j++)
            map[i][j] = server->map[i][j];
    }
    populate_map_with_players(map, client, server);
    for (int y = 0; y <= (int)client->level; y++) {
        for (int x = -y; x <= y; x++) {
            tile = map[(client->y + y) % server->proprieties.height]
                [(client->x + x) % server->proprieties.width];
            object_to_string(client, tile);
        }
    }
    if (asprintf(&client->payload, "%s ]\n", client->payload) == -1)
        return;
    client_time_handler(client, LOOK);
}
