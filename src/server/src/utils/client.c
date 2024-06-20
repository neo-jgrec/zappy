/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** client.c
*/

#include "client.h"
#include "server.h"

void client_time_handler(client_t *client, int command)
{
    signed char index = -1;
    char *tmp = NULL;

    for (unsigned char i = 0; i < NB_REQUESTS_HANDLEABLE; i++) {
        if (client->tclient[i].available_request == false) {
            index = i;
            client->tclient[i].available_request = true;
            client->tclient[i].command = command;
            handle_response(&tmp, "%s", client->payload);
            client->tclient[i].payload = tmp;
            break;
        }
    }
    if (index >= 0)
        clock_gettime(CLOCK_REALTIME, &client->tclient[index].future_time);
}
