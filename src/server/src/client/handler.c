/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handle.c
*/

#include "server.h"
#include <string.h>
#include <sys/types.h>

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

static int handle_quit_client(
    client_t *client,
    server_t *server,
    ssize_t check_read,
    int client_fd
)
{
    egg_t *egg;
    eggs_list_t *item_e;
    team_t *team;

    if (check_read != 0)
        return NEUTRAL_VALUE;
    if (client->is_graphic == false && client->is_connected == true) {
        message_to_graphicals(server, "pdi %d\n", client->id);
        egg = init_egg(client->x, client->y);
        item_e = malloc(sizeof(eggs_list_t));
        if (item_e == NULL)
            return ERROR_STATUS;
        team = get_team_by_name(&server->teams, client->team_name);
        item_e->egg = egg;
        TAILQ_INSERT_TAIL(&team->eggs, item_e, entries);
    }
    close(client_fd);
    FD_CLR(client_fd, &server->current_sockets);
    remove_client_by_fd(&server->clients, client_fd);
    return OK_STATUS;
}

static ssize_t read_until_newline(
    int client_fd,
    char *buffer,
    size_t buffer_size
)
{
    ssize_t total_read = 0;
    ssize_t bytes_read;

    while (total_read < (ssize_t)buffer_size - 1) {
        bytes_read = read(client_fd, buffer + total_read, 1);
        if (bytes_read < 0)
            return -1;
        if (bytes_read == 0)
            break;
        total_read += bytes_read;
        if (buffer[total_read - 1] == '\n')
            break;
    }
    buffer[total_read] = '\0';
    return total_read;
}

int handle_client_data(server_t *server, int client_fd)
{
    client_t *client = get_client(&server->clients, client_fd);
    ssize_t check_read;
    int quit_status;

    if (!client)
        return ERROR_STATUS;
    memset(client->message, '\0', sizeof(client->message));
    check_read = read_until_newline(client_fd,
        client->message, sizeof(client->message));
    if (check_read < 0) {
        close(client_fd);
        return ERROR_STATUS;
    }
    quit_status = handle_quit_client(client, server, check_read, client_fd);
    if (quit_status == OK_STATUS)
        return OK_STATUS;
    if (client->is_connected && quit_status == ERROR_STATUS)
        return ERROR_STATUS;
    handle_client_message(client, server);
    return OK_STATUS;
}
