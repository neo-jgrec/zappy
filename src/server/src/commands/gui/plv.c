/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** plv.c
*/

#include "server.h"

void plv(client_t *client, server_t *server)
{
    client_list_t *player;

    if (!client->commands[1]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    TAILQ_FOREACH(player, &server->clients, entries) {
        if (player->client->fd == atoi(client->commands[1])) {
            dprintf(client->fd, "plv %d %zu\n", player->client->fd,
                player->client->level);
            return;
        }
    }
    dprintf(client->fd, "sbp\n");
}
