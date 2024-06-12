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
    return client;
}

void destroy_clients(struct client_tailq *clients)
{
    client_list_t *item;

    while (!TAILQ_EMPTY(clients)) {
        item = TAILQ_FIRST(clients);
        TAILQ_REMOVE(clients, item, entries);
        free(item->client);
        free(item);
    }
}

void print_clients_fds(struct client_tailq *clients)
{
    client_list_t *item;

    TAILQ_FOREACH(item, clients, entries) {
        printf("FD: %d\n", item->client->fd);
    }
}
