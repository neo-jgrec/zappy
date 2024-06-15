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

static void execute_command(client_t *client, server_t *server)
{
    if (strlen(client->message) == 0)
        return;
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (client->is_connected == false)
            break;
        if (strcmp(client->commands[0], commands[i].name) == 0) {
            commands[i].command(client, server);
            free_array((void **)client->commands);
            return;
        }
    }
    if (connector(client, server) == false)
        dprintf(client->fd, "ko\n\r");
    free_array((void **)client->commands);
}

void handle_client_message(client_t *client, server_t *server)
{
    client->commands = str_to_array_separator(client->message, " \r\n\t");
    if (client->commands == NULL || client->commands[0] == NULL)
        return;
    execute_command(client, server);
}
