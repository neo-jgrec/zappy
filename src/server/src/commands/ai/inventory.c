/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** inventory.c
*/

#include "server.h"
#include "unused.h"

static const char fmt[] = "[food %d, linemate %d, \
deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d]\n";

void inventory(client_t *client, UNUSED server_t *server)
{
    int ret = 0;

    ret = asprintf(&client->payload, fmt,
        client->inventory.food,
        client->inventory.linemate,
        client->inventory.deraumere,
        client->inventory.sibur,
        client->inventory.mendiane,
        client->inventory.phiras,
        client->inventory.thystame
    );
    if (ret == -1) {
        perror("asprintf");
        return;
    }
    client_time_handler(client, INVENTORY);
}
