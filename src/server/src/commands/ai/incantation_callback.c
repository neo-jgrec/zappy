/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation.c
*/

#include "server.h"
#include "unused.h"

void callback_freeze(
    client_t *client,
    UNUSED server_t *server
)
{
    client->is_incanting = true;
}

void callback_level_up(
    client_t *client,
    UNUSED server_t *server
)
{
    client->level++;
}

void callback_unfreeze(
    client_t *client,
    UNUSED server_t *server
)
{
    client->is_incanting = false;
}

void callback_start_incantation_set_payload(
    client_t *client,
    UNUSED server_t *server
)
{
    asprintf(&client->payload, "Elevation underway\n");
}

void callback_end_incantation_set_payload(
    client_t *client,
    UNUSED server_t *server
)
{
    asprintf(&client->payload, "Current level: %zu\n", client->level);
}
