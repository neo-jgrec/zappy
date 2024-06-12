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

static void check_response_client_time(
        struct client_tailq *clients,
        double freq,
        struct timespec current
)
{
    client_list_t *item;
    double interval;
    double elapsed;
    struct timespec start;

    TAILQ_FOREACH(item, clients, entries) {
        for (unsigned char i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
            if (item->client->tclient[i].available_request) {
                start = item->client->tclient[i].future_time;
                interval = get_interval(item->client->tclient[i].command, freq);
                elapsed = (current.tv_sec - start.tv_sec) + (current.tv_nsec + start.tv_nsec) / NANOSECONDS_IN_SECOND;
                if (elapsed >= interval) {
                    dprintf(item->client->fd, "Finally!!!\n");
                }
            }
        }
        printf("FD(%d)\n", item->client->fd);
    }
}

static int start_server(server_t *server)
{
    double freq = (double)server->proprieties.frequency;

    while (true) {
        clock_gettime(CLOCK_REALTIME, &server->current_time);
        check_response_client_time(&server->clients, freq, server->current_time);
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
