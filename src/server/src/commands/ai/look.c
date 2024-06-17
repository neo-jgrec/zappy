#include "client.h"
#include "server.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

static const int dx[] = {0, 1, 0, -1};
static const int dy[] = {-1, 0, 1, 0};

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

static void populate_map_with_players(tile_t *map, server_t *server)
{
    client_list_t *tmp;
    client_t *client;

    TAILQ_FOREACH(tmp, &server->clients, entries) {
        client = tmp->client;
        int index = client->y * server->proprieties.width + client->x;
        map[index].num_objects++;
        map[index].objects = realloc(map[index].objects,
            map[index].num_objects * sizeof(object_t));
        map[index].objects[map[index].num_objects - 1] = PLAYER;
    }
}

static void check_object_in_lookup_table(object_t object, char **tile_payload)
{
    int ret_val = 0;
    char *new_tile_payload;

    for (size_t i = 0; object_handlers[i].name != NULL; i++) {
        if (object_handlers[i].type == object) {
            ret_val = asprintf(&new_tile_payload, "%s%s%s",
                *tile_payload, *tile_payload[0] ? " " : "",
                    object_handlers[i].name);
            break;
        }
    }
    if (ret_val != -1) {
        free(*tile_payload);
        *tile_payload = new_tile_payload;
    }
}

static void object_to_string(tile_t tile, char **tile_payload)
{
    for (size_t i = 0; i < tile.num_objects; i++) {
        check_object_in_lookup_table(tile.objects[i], tile_payload);
    }
}

static void append_tile_to_payload(client_t *client, tile_t *map, int index)
{
    char *tile_payload = strdup("");
    char *new_payload;

    if (tile_payload == NULL)
        return;
    object_to_string(map[index], &tile_payload);
    if (asprintf(&new_payload, "%s%s%s",
        client->payload, client->payload[1] ? "," : "", tile_payload) != -1) {
        free(client->payload);
        client->payload = new_payload;
    }
    free(tile_payload);
}

static void handle_look(client_t *c, server_t *server, tile_t *map)
{
    int w = server->proprieties.width;
    int h = server->proprieties.height;
    int d = c->orientation % 4;
    char *final_payload;
    int look_y;
    int look_x;

    free(c->payload);
    c->payload = strdup("[");
    if (c->payload == NULL)
        return;
    for (int level = 0; level <= (int)c->level; level++) {
        for (int offset = -level; offset <= level; offset++) {
            look_x = (c->x + dx[d] * level + dy[d] *offset + w) % w;
            look_y = (c->y + dy[d] * level - dx[d] * offset + h) % h;
            append_tile_to_payload(c, map, (look_y * w + look_x));
        }
    }
    if (asprintf(&final_payload, "%s ]\n", c->payload) != -1)
        c->payload = final_payload;
}

void look(client_t *client, server_t *server)
{
    tile_t *map = copy_map(calloc(server
        ->proprieties.width * server->proprieties.height,
        sizeof(tile_t)), server->map, server);

    if (map == NULL)
        return;
    populate_map_with_players(map, server);
    handle_look(client, server, map);
    for (int i = 0; i < server->proprieties.width *
        server->proprieties.height; i++)
        free(map[i].objects);
    free(map);
    client_time_handler(client, LOOK);
}
