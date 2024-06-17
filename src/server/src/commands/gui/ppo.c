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
        if (player->client->fd == atoi(client->commands[1])) {
            dprintf(client->fd, "ppo %d %u %u %u\n", player->client->fd,
                player->client->x, player->client->y,
                player->client->orientation);
            return;
        }
    }
    dprintf(client->fd, "sbp\n");
}
