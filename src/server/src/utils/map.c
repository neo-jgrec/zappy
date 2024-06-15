/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** map.c
*/

#include "server.h"

void add_element_to_map(server_t *server, int x, int y, object_t object)
{
    tile_t *tile = &server->map[y * server->proprieties.width + x];

    tile->objects[tile->num_objects] = object;
    tile->num_objects++;
}

void remove_element_from_map(server_t *server, int x, int y, object_t object)
{
    tile_t *tile = &server->map[y * server->proprieties.width + x];

    for (size_t i = 0; i < tile->num_objects; i++) {
        if (tile->objects[i] == object) {
            tile->objects[i] = tile->objects[tile->num_objects - 1];
            tile->num_objects--;
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
