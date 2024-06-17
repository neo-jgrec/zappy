/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** tna.c
*/

#include "server.h"

void tna(client_t *client, server_t *server)
{
    team_list_t *team;

    TAILQ_FOREACH(team, &server->teams, entries)
        dprintf(client->fd, "tna %s\n", team->team->name);
}
