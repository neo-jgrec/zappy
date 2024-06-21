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

static void print_egg_graphic(client_t *client, server_t *server)
{
    unsigned char cmd_idx = 0;

    if (client->is_incanting == true)
        return;
    if (client->tclient[cmd_idx].available_request)
        dprintf(client->fd, "%s", client->tclient[cmd_idx].payload);
    if (client->tclient[cmd_idx].command == FORK)
        message_to_graphicals(server, "enw %d %s %d %d\n", client->egg_id,
            client->id, client->x, client->y);
    for (unsigned char idx = 0; idx < NB_REQUESTS_HANDLEABLE; idx++) {
        if (idx + 1 < NB_REQUESTS_HANDLEABLE)
            client->tclient[idx] = client->tclient[idx + 1];
        else {
            client->tclient[idx].command = -1;
            client->tclient[idx].available_request = false;
        }
        if (client->tclient[idx].available_request)
            clock_gettime(CLOCK_REALTIME, &client->tclient[idx].future_time);
        else
            client->tclient[idx].command = 0;
    }
}

static bool send_command(
    client_t *client,
    struct timespec *curr,
    server_t *server
)
{
    struct timespec cmd_start_time;
    double interval;
    double elapsed;
    unsigned char cmd_idx = 0;

    if (client->tclient[cmd_idx].available_request) {
        cmd_start_time = client->tclient[cmd_idx].future_time;
        interval = get_interval(client->tclient[cmd_idx].command,
        server->proprieties.frequency);
        elapsed = (curr->tv_sec - cmd_start_time.tv_sec) + ((curr
            ->tv_nsec - cmd_start_time.tv_nsec) / NANOSECONDS_IN_SECOND);
        if (elapsed >= interval
            && client->tclient[cmd_idx].command == INCANTATION)
            incantation_callback_end_of_command(client, NULL);
        if (client->level == LAST_LEVEL)
            return true;
        if (elapsed >= interval)
            print_egg_graphic(client, server);
    }
    return false;
}

static bool check_response_client_time(
    struct client_tailq *clients,
    server_t *server,
    struct timespec *current
)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        if (send_command(item->client, current, server) == true)
            return true;
    }
    return false;
}

static int start_server(server_t *server)
{
    while (true) {
        server->ready_sockets = server->current_sockets;
        clock_gettime(CLOCK_REALTIME, &server->current_time);
        if (handle_client_life(server) == true)
            continue;
        handle_meteors(server);
        if (check_response_client_time(&server->clients,
            server, &server->current_time) == true)
            break;
        if (select(FD_SETSIZE, &server->ready_sockets,
            NULL, NULL, &server->timeout) < 0) {
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
