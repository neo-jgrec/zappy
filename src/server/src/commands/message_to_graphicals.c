/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** send gui
*/

#include "client.h"
#include "server.h"
#include <stdarg.h>

void message_to_graphicals(server_t *server, char *fmt, ...)
{
    client_list_t *client;
    va_list args;

    if (fmt == NULL)
        return;
    TAILQ_FOREACH(client, &server->clients, entries) {
        if (client->client && client->client->is_graphic) {
            va_start(args, fmt);
            vdprintf(client->client->fd, fmt, args);
            va_end(args);
        }
    }
}
