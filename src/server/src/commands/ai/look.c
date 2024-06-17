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
    {FOOD, "food"},
    {LINEMATE, "linemate"},
    {DERAUMERE, "deraumere"},
    {SIBUR, "sibur"},
    {MENDIANE, "mendiane"},
    {PHIRAS, "phiras"},
    {THYSTAME, "thystame"},
    {PLAYER, "player"},
    {EMPTY, ""},
    {0, NULL}
};

static tile_t *copy_map(tile_t *dest, tile_t *src, server_t *server)
{
    if (dest == NULL)
        return NULL;
    for (int i = 0; i < server->
        proprieties.width * server->proprieties.height; i++) {
        dest[i].num_objects = src[i].num_objects;
        dest[i].objects = malloc(sizeof(object_t) * src[i].num_objects);
        if (dest[i].objects == NULL)
            return NULL;
        for (size_t j = 0; j < src[i].num_objects; j++)
            dest[i].objects[j] = src[i].objects[j];
    }
    return dest;
}

static void populate_map_with_players(
    tile_t *map,
    server_t *server
)
{
    client_list_t *tmp;
    client_t *client;

    TAILQ_FOREACH(tmp, &server->clients, entries) {
        client = tmp->client;
        map[client->y].num_objects++;
        map[client->y].objects = realloc(map[client->y].objects,
            map[client->y].num_objects * sizeof(object_t));
        map[client->y].objects[map[client->y].num_objects - 1] = PLAYER;
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
    tile_t *map = copy_map(calloc(
        server->proprieties.width * server->proprieties.height,
        sizeof(tile_t)), server->map, server);
    tile_t tile;

    if (map == NULL)
        return;
    client->payload = "[";
    populate_map_with_players(map, server);
    for (int y = 0; y <= (int)client->level; y++) {
        for (int x = -y; x <= y; x++) {
            tile = map[(client->y + y) % server->proprieties.height];
            object_to_string(client, tile);
        }
    }
    if (asprintf(&client->payload, "%s ]\n", client->payload) == -1)
        return;
    free(map);
    client_time_handler(client, LOOK);
}
