/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** pin.c
*/

#include "server.h"

void pin(client_t *client, server_t *server)
{
    client_list_t *c;

    if (!client->commands[1]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    TAILQ_FOREACH(c, &server->clients, entries) {
        if (strcmp(c->client->uuid, client->commands[1]) == 0) {
            dprintf(client->fd, "pin %s %u %u %u %u %u %u %u %u %u\n",
                c->client->uuid, c->client->x, c->client->y,
                c->client->inventory.food, c->client->inventory.linemate,
                c->client->inventory.deraumere, c->client->inventory.sibur,
                c->client->inventory.mendiane, c->client->inventory.phiras,
                c->client->inventory.thystame
            );
            return;
        }
    }
    dprintf(client->fd, "sbp\n");
}
