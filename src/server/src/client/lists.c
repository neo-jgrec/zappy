/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** lists.c
*/

#include "server.h"

const int orientations[4] = {NORTH, SOUTH, WEST, EAST};

static void init_inventory(inventory_t *inv)
{
    inv->thystame = 0;
    inv->phiras = 0;
    inv->mendiane = 0;
    inv->sibur = 0;
    inv->deraumere = 0;
    inv->linemate = 0;
    inv->food = 10;
}

static void init_bools(client_t *client)
{
    client->is_incanting = false;
    client->is_connected = false;
    client->is_graphic = false;
}

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
    client->level = 1;
    init_bools(client);
    client->orientation = orientations[rand_p(4)];
    client->payload = NULL;
    init_inventory(&client->inventory);
    client->egg_id = 0;
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
