/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ppo.c
*/

#include "server.h"

void ppo(client_t *client, server_t *server)
{
    client_list_t *player;

    if (!client->commands[1]) {
        dprintf(client->fd, "sbp\n");
        return;
    }
    TAILQ_FOREACH(player, &server->clients, entries) {
        if (strcmp(player->client->uuid, client->commands[1]) == 0) {
            dprintf(client->fd, "ppo %s %u %u %u\n", player->client->uuid,
                player->client->x, player->client->y,
                player->client->orientation);
            return;
        }
    }
    dprintf(client->fd, "sbp\n");
}
