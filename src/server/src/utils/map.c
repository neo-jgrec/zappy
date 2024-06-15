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

void remove_element_from_map(server_t *server, int x, int y, object_t object)
{
    for (size_t i = 0; i < server->map[y * server->proprieties.width + x]
        .num_objects; i++) {
        if (server->map[y * server->proprieties.width + x]
            .objects[i] == object) {
            server->map[y * server->proprieties.width + x].objects[i] =
                server->map[y * server->proprieties.width + x]
                    .objects[server->map[y * server->proprieties.width + x]
                    .num_objects - 1];
            server->map[y * server->proprieties.width + x].num_objects--;
            server->map[y * server->proprieties.width + x].objects =
                realloc(server->map[y * server->proprieties.width + x].objects,
                    sizeof(object_t) * server
                        ->map[y * server->proprieties.width + x]
                        .num_objects);
            break;
        }
    }
}

info_map_t get_map_density(server_t *server, int x, int y)
{
    info_map_t d = {0};

    for (size_t i = 0; i < server->map[y * server->proprieties.width + x]
        .num_objects; i++) {
        d.deraumere = (server->map[y * server->proprieties.width + x]
            .objects[i] == DERAUMERE ? d.deraumere + 1 : d.deraumere);
        d.food = (server->map[y * server->proprieties.width + x]
            .objects[i] == FOOD ? d.food + 1 : d.food);
        d.linemate = (server->map[y * server->proprieties.width + x]
            .objects[i] == LINEMATE ? d.linemate + 1 : d.linemate);
        d.mendiane = (server->map[y * server->proprieties.width + x]
            .objects[i] == MENDIANE ? d.mendiane + 1 : d.mendiane);
        d.phiras = (server->map[y * server->proprieties.width + x]
            .objects[i] == PHIRAS ? d.phiras + 1 : d.phiras);
        d.sibur = (server->map[y * server->proprieties.width + x]
            .objects[i] == SIBUR ? d.sibur + 1 : d.sibur);
        d.thystame = (server->map[y * server->proprieties.width + x]
            .objects[i] == THYSTAME ? d.thystame + 1 : d.thystame);
    }
    return d;
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
