/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init.c
*/

#include "server.h"
#include <string.h>
#include <stdio.h>

static struct sockaddr_in init_socket_address(size_t port)
{
    struct sockaddr_in info;

    memset(&info, 0, sizeof(info));
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = htonl(INADDR_ANY);
    return info;
}

static bool init_teams(server_t *server)
{
    char **teams = server->proprieties.names;
    int nb_clients = server->proprieties.nb_clients;
    int width = server->proprieties.width;
    int height = server->proprieties.height;
    team_list_t *new_team;

    for (size_t i = 0; teams[i] != NULL; i++) {
        new_team = malloc(sizeof(team_list_t));
        if (new_team == NULL)
            return false;
        new_team->team = init_team(teams[i], nb_clients, width, height);
        if (new_team->team == NULL)
            return false;
        TAILQ_INSERT_TAIL(&server->teams, new_team, entries);
    }
    return true;
}

static tile_t *init_map(int width, int height)
{
    tile_t *map = calloc(height * width, sizeof(tile_t));

    if (map == NULL)
        return NULL;
    for (int i = 0; i < height * width; i++) {
        map[i].num_objects = 0;
        map[i].objects = NULL;
    }
    return map;
}

static void add_object(int obj, int obj_enum, server_t *server)
{
    int x = server->proprieties.width;
    int y = server->proprieties.height;

    for (int i = obj; i >= 0; i--)
        add_element_to_map(server, rand_p(x), rand_p(y), obj_enum);
}

static void init_meteor(server_t *server)
{
    info_map_t objs = server->proprieties.max_map;

    add_object(objs.food, FOOD, server);
    add_object(objs.linemate, LINEMATE, server);
    add_object(objs.deraumere, DERAUMERE, server);
    add_object(objs.sibur, SIBUR, server);
    add_object(objs.mendiane, MENDIANE, server);
    add_object(objs.phiras, PHIRAS, server);
    add_object(objs.thystame, THYSTAME, server);
    clock_gettime(CLOCK_REALTIME, &server->meteor_last_time);
}

bool init_server(server_t *server, const char **args)
{
    if (init_flags(&server->proprieties, args) == false)
        return false;
    TAILQ_INIT(&server->teams);
    if (init_teams(server) == false)
        return false;
    TAILQ_INIT(&server->clients);
    print_teams_infos(&server->teams);
    server->info = init_socket_address((size_t)server->proprieties.port);
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    server->addrlen = sizeof(struct sockaddr_in);
    if (server->fd < 0)
        return false;
    FD_ZERO(&server->current_sockets);
    FD_SET(server->fd, &server->current_sockets);
    server->timeout.tv_sec = 0;
    server->timeout.tv_usec = 0;
    server->map = init_map(server->proprieties.width,
        server->proprieties.height);
    init_meteor(server);
    return true;
}
