/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handle.c
*/

#include "server.h"
#include <string.h>

static int accept_new_client(server_t *server)
{
    struct sockaddr_in info;
    socklen_t addrlen = sizeof(info);
    int client_fd = accept(server->fd, (struct sockaddr *)&info, &addrlen);

    if (client_fd < 0) {
        perror("Accept failed");
        return -1;
    }
    return client_fd;
}

int create_new_client(server_t *server)
{
    int client_fd = accept_new_client(server);
    client_list_t *new_client;

    if (client_fd == -1)
        return ERROR_STATUS;
    dprintf(client_fd, "WELCOME\n");
    new_client = malloc(sizeof(client_list_t));
    if (!new_client) {
        perror("Malloc while creating a client failed");
        return ERROR_STATUS;
    }
    new_client->client = init_client(client_fd);
    if (!new_client->client) {
        free(new_client);
        return ERROR_STATUS;
    }
    TAILQ_INSERT_TAIL(&server->clients, new_client, entries);
    FD_SET(client_fd, &server->current_sockets);
    return OK_STATUS;
}

client_t *get_client(struct client_tailq *clients, int client_fd)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        if (item->client->fd == client_fd) {
            return item->client;
        }
    }
    return NULL;
}

int handle_client_data(server_t *server, int client_fd)
{
    client_t *client = get_client(&server->clients, client_fd);
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
