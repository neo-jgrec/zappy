/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handler.c
*/

#include "server.h"

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

void handle_client_message(server_t *server)
{
    client_t *client = server->clients;

    if (strlen(client->message) == 0)
        return;
    client->commands = str_to_array_separator(client->message, " \r\n\t");
    memset(client->message, '\0', BUFFER_SIZE);
    if (client->commands == NULL || client->commands[0] == NULL)
        return;
    for (size_t i = 0; i < NB_COMMANDS; i++) {
        if (strcmp(client->commands[0], commands[i].name) == 0) {
            commands[i].command(client, server);
            free_array((void **)client->commands);
            return;
        }
    }
    free_array((void **)client->commands);
    dprintf(client->fd, "ko\n\r");
}
