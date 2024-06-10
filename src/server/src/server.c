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

static int start_server(server_t *server)
{
    while (true) {
        server->ready_sockets = server->current_sockets;
        if (select(FD_SETSIZE, &server->ready_sockets, NULL, NULL, NULL) < 0) {
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

    if (!init_server(&server, args)) {
        destroy_server(server);
        return helper(ERROR_STATUS);
    }
    if (bind(server.fd, (struct sockaddr *)&server.info, server.addrlen) < 0)
        status = ERROR_STATUS;
    if (listen(server.fd, FD_SETSIZE) < 0)
        status = ERROR_STATUS;
    srand(time(NULL));
    if (start_server(&server) == ERROR_STATUS)
        status = ERROR_STATUS;
    if (status == ERROR_STATUS)
        close(server.fd);
    destroy_server(server);
    return status;
}
