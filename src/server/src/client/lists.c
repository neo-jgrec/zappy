/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** lists.c
*/

#include "server.h"

client_t *init_client(int client_fd)
{
    uuid_t binuuid;
    client_t *client = malloc(sizeof(client_t));

    if (client == NULL)
        return NULL;
    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, client->uuid);
    client->commands = NULL;
    client->fd = client_fd;
    for (unsigned char i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
        client->tclient[i].available_request = false;
        client->tclient[i].command = -1;
    }
    client->is_connected = false;
    client->is_graphic = false;
    return client;
}

void destroy_clients(struct client_tailq *clients)
{
    client_list_t *item;

    while (!TAILQ_EMPTY(clients)) {
        item = TAILQ_FIRST(clients);
        TAILQ_REMOVE(clients, item, entries);
        secure_free(item->client);
        secure_free(item);
    }
}

void remove_client_by_fd(struct client_tailq *clients, int fd)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        if (item->client->fd == fd) {
            TAILQ_REMOVE(clients, item, entries);
            secure_free(item->client);
            item->client = NULL;
            break;
        }
    }
}

void print_clients_fds(struct client_tailq *clients)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        printf("FD: %d\n", item->client->fd);
    }
}
