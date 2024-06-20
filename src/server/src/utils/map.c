/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map.c
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

void add_element_to_map(server_t *server, int x, int y, object_t object)
{
    server->map[y * server->proprieties.width + x].objects =
        realloc(server->map[y * server->proprieties.width + x].objects,
            sizeof(object_t) * (server->map[y * server->proprieties.width + x]
                .num_objects + 1));
    server->map[y * server->proprieties.width + x].objects[server->map[y *
        server->proprieties.width + x].num_objects] = object;
    server->map[y * server->proprieties.width + x].num_objects++;
}

void remove_element_from_map(server_t *s, int x, int y, object_t o)
{
    for (size_t i = 0; i < s->map[y * s->proprieties.width + x]
        .num_objects; i++) {
        if (s->map[y * s->proprieties.width + x].objects[i] != o)
            continue;
        s->map[y * s->proprieties.width + x].objects[i] =
            s->map[y * s->proprieties.width + x]
                .objects[s->map[y * s->proprieties.width + x]
                .num_objects - 1];
        s->map[y * s->proprieties.width + x].num_objects--;
        if (s->map[y * s->proprieties.width + x].num_objects > 0) {
            s->map[y * s->proprieties.width + x].objects =
                realloc(s->map[y * s->proprieties.width + x].objects,
                    sizeof(object_t) * s->map[y * s->proprieties.width + x]
                        .num_objects);
        } else {
            free(s->map[y * s->proprieties.width + x].objects);
            s->map[y * s->proprieties.width + x].objects = NULL;
        }
        break;
    }
}

info_map_t get_map_density(server_t *server)
{
    info_map_t info_map = {0};
    int map_size = server->proprieties.width * server->proprieties.height;
    tile_t *cell = NULL;

    for (int idx = 0; idx < map_size; idx++) {
        cell = &server->map[idx];
        for (size_t k = 0; k < cell->num_objects; k++) {
            info_map.food += (cell->objects[k] == FOOD);
            info_map.linemate += (cell->objects[k] == LINEMATE);
            info_map.deraumere += (cell->objects[k] == DERAUMERE);
            info_map.sibur += (cell->objects[k] == SIBUR);
            info_map.mendiane += (cell->objects[k] == MENDIANE);
            info_map.phiras += (cell->objects[k] == PHIRAS);
            info_map.thystame += (cell->objects[k] == THYSTAME);
        }
    }
    return info_map;
}

void print_tile(tile_t *tile)
{
    dprintf(1, "[");
    for (size_t k = 0; k < tile->num_objects; k++) {
        dprintf(1, "%s%s", object_handlers[tile->objects[k]].name,
                k + 1 < tile->num_objects ? ", " : "");
    }
    dprintf(1, "]");
}

void print_map(server_t *server)
{
    for (int i = 0; i < server->proprieties.height; i++) {
        for (int j = 0; j < server->proprieties.width; j++) {
            dprintf(1, "%d, %d, ", j, i);
            print_tile(&server->map[i * server->proprieties.width + j]);
            dprintf(1, "%s", j + 1 < server->proprieties.width ? ", " : "");
        }
        dprintf(1, "\n");
    }
}
