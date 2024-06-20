/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** fork.c
*/

#include "client.h"
#include "server.h"

void fork_z(client_t *c, server_t *server)
{
    eggs_list_t *new_egg = malloc(sizeof(eggs_list_t));
    team_t *team = get_team_by_name(&server->teams, c->team_name);

    if (new_egg == NULL || team == NULL)
        return;
    new_egg->egg = init_egg(server->proprieties.width,
    server->proprieties.height);
    if (new_egg->egg == NULL)
        return;
    TAILQ_INSERT_TAIL(&team->eggs, new_egg, entries);
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == false) {
        message_to_graphicals(server, "pfk %d\n", c->fd);
        handle_response(&c->payload, "ok\n");
    } else
        handle_response(&c->payload, "ko\n");
    client_time_handler(c, FORK);
}
