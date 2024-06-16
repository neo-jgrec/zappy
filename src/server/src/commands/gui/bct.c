/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** bct.c
*/

#include "flags.h"
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

void bct(client_t *client, server_t *server)
{
    size_t x;
    size_t y;
    info_map_t info;

    if (!client->commands[1] || !client->commands[2]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    x = atoi(client->commands[1]);
    y = atoi(client->commands[2]);
    if (x >= (size_t)server->proprieties.width
        || y >= (size_t)server->proprieties.height) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    info = get_tile(server, x, y);
    dprintf(client->fd, "bct %ld %ld %d %d %d %d %d %d %d\n",
        x, y, info.food, info.linemate, info.deraumere, info.sibur,
        info.mendiane, info.phiras, info.thystame
    );
}
