/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** connect_nbr.c
*/

#include "server.h"

void connect_nbr(client_t *client, server_t *server)
{
    size_t nb_slots = team_nb_slots(&server->teams, client->team_name);

    dprintf(client->fd, "%zu\n", nb_slots);
}
