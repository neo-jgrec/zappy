/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handle.c
*/

#include "server.h"

static int accept_new_client(server_t *server)
{
    struct sockaddr_in info;
    socklen_t addrlen;
    int client_fd = accept(server->fd, (struct sockaddr *)&info, &addrlen);

    if ((client_fd) < 0) {
        close(client_fd);
        perror("Accept failed");
        return -1;
    }
    return client_fd;
}

int create_new_client(server_t *server)
{
    int client_fd = accept_new_client(server);

    if (client_fd == -1)
        return ERROR_STATUS;
    printf("New client created\n");
    if (server->clients == NULL)
        server->clients = init_client(client_fd);
    else if (push_client(server->clients, client_fd) == false)
        return ERROR_STATUS;
    FD_SET(client_fd, &server->current_sockets);
    return OK_STATUS;
}

client_t *get_client(client_t *clients, int client_fd)
{
    client_t *tmp = NULL;

    for (; clients; clients = clients->next) {
        if (clients->fd == client_fd) {
            tmp = clients;
            break;
        }
    }
    return tmp;
}

int handle_client_data(server_t *server, int client_fd)
{
    client_t *client = get_client(server->clients, client_fd);
    ssize_t check_read;

    if (!client) {
        perror("Client not found");
        return ERROR_STATUS;
    }
    memset(client->message, '\0', sizeof(client->message));
    check_read = read(client_fd, client->message, sizeof(client->message));
    if (check_read < 0) {
        close(client_fd);
        return ERROR_STATUS;
    }
    if (check_read == 0) {
        close(client_fd);
        FD_CLR(client_fd, &server->current_sockets);
        return OK_STATUS;
    }
    handle_client_message(server);
    return OK_STATUS;
}
