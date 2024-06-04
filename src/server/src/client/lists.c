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
    client->next = NULL;
    client->prev = NULL;
    client->commands = NULL;
    client->fd = client_fd;
    return client;
}

void free_clients(client_t *clients)
{
    client_t *next_client;

    if (!clients)
        return;
    for (; clients->prev; clients = clients->prev);
    while (clients) {
        next_client = clients->next;
        free_array((void **)clients->commands);
        free(clients);
        clients = next_client;
    }
    clients = NULL;
}

void print_clients_fds(client_t *clients)
{
    while (clients != NULL) {
        printf("[%d]", clients->fd);
        if (clients->next != NULL)
            printf("-");
        clients = clients->next;
    }
    printf("\n");
}

bool push_client(client_t *client, int client_fd)
{
    client_t *new_client = init_client(client_fd);

    if (new_client == NULL)
        return false;
    if (client == NULL) {
        client = new_client;
        return true;
    }
    for (; client->next; client = client->next);
    client->next = new_client;
    new_client->prev = client;
    return true;
}
