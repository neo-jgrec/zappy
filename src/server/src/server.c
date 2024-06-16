/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server.c
*/

#include "server.h"
#include <time.h>

static int handle_connections(server_t *server, int fd)
{
    if (FD_ISSET(fd, &server->ready_sockets)) {
        if (fd == server->fd && create_new_client(server) == ERROR_STATUS)
            return ERROR_STATUS;
        if (fd != server->fd &&
            handle_client_data(server, fd) == ERROR_STATUS)
            return ERROR_STATUS;
    }
    return OK_STATUS;
}

static int check_connections(server_t *server)
{
    for (int i = 0; i < FD_SETSIZE; i++) {
        if (handle_connections(server, i) == ERROR_STATUS)
            return ERROR_STATUS;
    }
    return OK_STATUS;
}

static double get_interval(int command, double freq)
{
    const interval_t intervals[NB_COMMANDS_TO_SEND] = {
            {FORWARD, FORWARD_TLIMIT},
            {RIGHT, RIGHT_TLIMIT},
            {LEFT, LEFT_TLIMIT},
            {LOOK, LOOK_TLIMIT},
            {INVENTORY, INVENTORY_TLIMIT},
            {BROADCAST, BROADCAST_TLIMIT},
            {FORK, FORK_TLIMIT},
            {EJECT, EJECT_TLIMIT},
            {TAKE, TAKE_TLIMIT},
            {SET, SET_TLIMIT},
            {INCANTATION, INCANTATION_TLIMIT}
    };

    for (unsigned char i = 0; i < NB_COMMANDS_TO_SEND; i++) {
        if (intervals[i].command == command)
            return freq > 0.0f ? intervals[i].frequency / freq : -1.0f;
    }
    return -1.0f;
}

static void send_command(
    client_t *client,
    unsigned char i,
    struct timespec *current,
    double freq
)
{
    struct timespec cmd_start_time;
    double interval;
    double elapsed;
    time_t sec_sus;
    time_t nsec_sus;

    if (client->tclient[i].available_request) {
        cmd_start_time = client->tclient[i].future_time;
        interval = get_interval(client->tclient[i].command, freq);
        sec_sus = (current->tv_sec - cmd_start_time.tv_sec);
        nsec_sus = (current->tv_nsec + cmd_start_time.tv_nsec);
        elapsed = sec_sus + nsec_sus / NANOSECONDS_IN_SECOND;
        if (elapsed >= interval) {
            dprintf(client->fd, "%s", client->payload);
        }
    }
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
    add_object(server, max->food, map->food, FOOD);
    add_object(server, max->linemate, map->linemate, LINEMATE);
    add_object(server, max->deraumere, map->deraumere, DERAUMERE);
    add_object(server, max->sibur, map->sibur, SIBUR);
    add_object(server, max->mendiane, map->mendiane, MENDIANE);
    add_object(server, max->phiras, map->phiras, PHIRAS);
    add_object(server, max->thystame, map->thystame, THYSTAME);
}

static void handle_meteors(server_t *server)
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
        print_map(server);
        if (map.thystame != max_map.thystame || map.phiras != max_map.phiras ||
            map.mendiane != max_map.mendiane || map.sibur != max_map.sibur ||
            map.linemate != max_map.linemate || map.food != max_map.food ||
            map.deraumere != max_map.deraumere)
            fill_objects(server, &max_map, &map);
    }
    METEORS_LIMIT;
}

static void check_response_client_time(
    struct client_tailq *clients,
    double freq,
    struct timespec *current
)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        for (unsigned char i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
            send_command(item->client, i, current, freq);
        }
    }
}

static int start_server(server_t *server)
{
    double freq = (double)server->proprieties.frequency;

    while (true) {
        clock_gettime(CLOCK_REALTIME, &server->current_time);
        handle_meteors(server);
        check_response_client_time(&server->clients, freq,
            &server->current_time);
        server->ready_sockets = server->current_sockets;
        if (select(FD_SETSIZE, &server->ready_sockets, NULL, NULL,
            &server->timeout) < 0) {
            perror("There was an error in select");
            return ERROR_STATUS;
        }
        if (check_connections(server) == ERROR_STATUS)
            return ERROR_STATUS;
    }
    return OK_STATUS;
}

int server(const char **args)
{
    int status = OK_STATUS;
    server_t server = {0};

    srand(time(NULL));
    if (!init_server(&server, args)) {
        destroy_server(server);
        return helper(ERROR_STATUS);
    }
    if (bind(server.fd, (struct sockaddr *)&server.info, server.addrlen) < 0)
        status = ERROR_STATUS;
    if (listen(server.fd, FD_SETSIZE) < 0)
        status = ERROR_STATUS;
    if (start_server(&server) == ERROR_STATUS)
        status = ERROR_STATUS;
    if (status == ERROR_STATUS)
        close(server.fd);
    destroy_server(server);
    return status;
}
