/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** client.c
*/

#include "server.h"

void client_time_handler(client_t *client, int command)
{
    signed char index = -1;

    for (unsigned char i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
        if (client->tclient[i].available_request == false) {
            index = i;
            client->tclient[i].available_request = true;
            client->tclient[i].command = command;
            break;
        }
    }
    dprintf(client->fd, "JUST GOT %u\n", index);
    if (index >= 0)
        clock_gettime(CLOCK_REALTIME, &client->tclient[index].future_time);
}
