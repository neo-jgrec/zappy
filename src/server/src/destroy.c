/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** destroy.c
*/

#include "server.h"

void destroy_flags(flags_t *flags)
{
    if (flags == NULL)
        return;
    if (flags->names == NULL)
        return;
    for (size_t i = 0; flags->names[i] != NULL; i++) {
        secure_free((void **)&flags->names[i]);
    }
    free(flags->names);
}

void destroy_server(server_t server)
{
    destroy_flags(&server.proprieties);
    destroy_clients(&server.clients);
    destroy_teams(&server.teams);
}
