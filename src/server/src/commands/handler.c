/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** handler.c
*/

#include "server.h"

const commands_t commands_gui[NB_GUI_COMMANDS] = {
    {"msz", msz},
    {"bct", bct},
    {"mct", mct},
    {"tna", tna},
    {"ppo", ppo},
    {"plv", plv},
    {"pin", pin},
    {"sgt", sgt},
    {"sst", sst}
};

const commands_t commands_ai[NB_AI_COMMANDS] = {
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
    size_t nb_commands;
    char *name;

    if (client->is_connected == false)
        return false;
    nb_commands = client->is_graphic ? NB_GUI_COMMANDS : NB_AI_COMMANDS;
    for (size_t i = 0; i < nb_commands; i++) {
        name = client->is_graphic ? commands_gui[i].name : commands_ai[i].name;
        if (strcmp(client->commands[0], name) != 0)
            continue;
        printf("Executing command: %s\n", name);
        if (client->is_graphic)
            commands_gui[i].command(client, server);
        else
            commands_ai[i].command(client, server);
        printf("Payload after command execution: %s\n", client->payload);
        free_array((void **)client->commands);
        return true;
    }
    if (client->is_graphic)
        message_to_graphicals(server, "sbp\n");
    return false;
}

void handle_client_message(client_t *client, server_t *server)
{
    client->commands = str_to_array_separator(client->message, " \n\t");
    if (client->commands == NULL || client->commands[0] == NULL)
        return;

    if (execute_command(client, server) == true) {
        printf("Sending payload: %s\n", client->payload);
        return;
    }

    if (connector(client, server) == false) {
        if (client->is_graphic == false)
            dprintf(client->fd, "ko\n");
        free_array((void **)client->commands);
        return;
    }
}
