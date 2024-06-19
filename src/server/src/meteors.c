/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** meteors.c
*/

#include "server.h"

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

static void add_object(server_t *server, int max, int value, int obj_enum)
{
    int diff = max - value;
    int x = server->proprieties.width;
    int y = server->proprieties.height;

    for (int i = diff; i >= 0; i--)
        add_element_to_map(server, rand_p(x), rand_p(y), obj_enum);
}

static void fill_objects(server_t *server, info_map_t *max, info_map_t *map)
{
    info_map_t info;

    add_object(server, max->food, map->food, FOOD);
    add_object(server, max->linemate, map->linemate, LINEMATE);
    add_object(server, max->deraumere, map->deraumere, DERAUMERE);
    add_object(server, max->sibur, map->sibur, SIBUR);
    add_object(server, max->mendiane, map->mendiane, MENDIANE);
    add_object(server, max->phiras, map->phiras, PHIRAS);
    add_object(server, max->thystame, map->thystame, THYSTAME);
    for (size_t y = 0; y < (size_t)server->proprieties.height; y++) {
        for (size_t x = 0; x < (size_t)server->proprieties.width; x++) {
            info = get_tile(server, x, y);
            message_to_graphicals(server, "bct %ld %ld %d %d %d %d %d %d %d\n",
            x, y, info.food, info.linemate, info.deraumere, info.sibur,
            info.mendiane, info.phiras, info.thystame
            );
        }
    }
}

void handle_meteors(server_t *server)
{
    struct timespec current = server->current_time;
    struct timespec meteor_time = server->meteor_last_time;
    double interval = METEORS_LIMIT / (double)server->proprieties.frequency;
    time_t sec_sus = (current.tv_sec - meteor_time.tv_sec);
    time_t nsec_sus = (current.tv_nsec + meteor_time.tv_nsec);
    double elapsed = sec_sus + nsec_sus / NANOSECONDS_IN_SECOND;
    info_map_t map;
    info_map_t max_map = server->proprieties.max_map;

    if (elapsed >= interval) {
        map = get_map_density(server);
        clock_gettime(CLOCK_REALTIME, &server->meteor_last_time);
        if (map.thystame != max_map.thystame || map.phiras != max_map.phiras ||
            map.mendiane != max_map.mendiane || map.sibur != max_map.sibur ||
            map.linemate != max_map.linemate || map.food != max_map.food ||
            map.deraumere != max_map.deraumere)
            fill_objects(server, &max_map, &map);
    }
}
