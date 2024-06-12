/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handler.c
*/

#include "server.h"
#include <strings.h>

const commands_t commands[NB_COMMANDS] = {
    {"Forward", forward},
    {"Right", right},
    {"Left", left},
    {"Look", look},
    {"Inventory", inventory},
    {"Broadcast", broadcast},
    {"Connect_nbr", connect_nbr},
    {"Fork", fork_z},
    {"Eject", eject},
    {"Take", take},
    {"Set", set},
    {"Incantation", incantation},
};

static bool execute_command(client_t *client, server_t *server)
{
    if (strlen(client->message) == 0)
        return false;
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(client->commands[0], commands[i].name) == 0) {
            commands[i].command(client, server);
            free_array((void **)client->commands);
            return true;
        }
    }
    free_array((void **)client->commands);
    dprintf(client->fd, "ko\n\r");
    return false;
}

void handle_client_message(server_t *server)
{
    client_list_t *item;
    client_t *client;

    TAILQ_FOREACH(item, &server->clients, entries) {
        client = item->client;
        client->commands = str_to_array_separator(client->message, " \r\n\t");
        if (client->commands == NULL || client->commands[0] == NULL)
            continue;
        if (!execute_command(client, server))
            continue;
    }
}
