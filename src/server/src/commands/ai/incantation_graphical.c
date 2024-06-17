/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** incantation.c
*/

#include "client.h"
#include "server.h"

void send_start_incantation_to_graphicals(client_t *client, server_t *server)
{
    char *uuids = NULL;
    client_list_t *list;
    int ret = asprintf(&uuids, "%s", client->uuid);

    TAILQ_FOREACH(list, &server->clients, entries) {
        if (list->client->x == client->x
            && list->client->y == client->y
            && list->client->is_incanting
            && list->client != client) {
            ret = asprintf(&uuids, "%s %s", uuids, list->client->uuid);
        }
    }
    if (ret == -1)
        return;
    message_to_graphicals(server, "pic %hhd %hhd %zu %s\n",
        client->x, client->y, client->level, uuids);
}
