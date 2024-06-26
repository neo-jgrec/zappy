/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** death.c
*/

#include "server.h"

static void send_pin_for_food_update(client_t *client, server_t *s)
{
    message_to_graphicals(s, "pin %d %d %d %d %d %d %d %d %d %d\n",
        client->id, client->x, client->y, client->inventory.food,
        client->inventory.linemate, client->inventory.deraumere,
        client->inventory.sibur, client->inventory.mendiane,
        client->inventory.phiras, client->inventory.thystame);
}

static bool handle_client_death(
    client_t *client,
    server_t *s,
    time_t sec_sus,
    long nsec_sus
)
{
    double elapsed = sec_sus + (nsec_sus / (double)NANOSECONDS_IN_SECOND);
    double interval = PLAYER_LIFE_LIMIT / (double)s->proprieties.frequency;

    if (elapsed >= interval) {
        client->inventory.food -= 1;
        clock_gettime(CLOCK_REALTIME, &client->live_time);
        send_pin_for_food_update(client, s);
    }
    if (client->inventory.food == 0) {
        dprintf(client->fd, "dead\n");
        close(client->fd);
        FD_CLR(client->fd, &s->current_sockets);
        message_to_graphicals(s, "pdi %d\n", client->id);
        remove_client_by_fd(&s->clients, client->fd);
        return true;
    }
    return false;
}

bool handle_client_life(server_t *s)
{
    struct timespec current = s->current_time;
    struct timespec live_time;
    client_t *client;
    time_t sec_sus;
    long nsec_sus;

    for (client_list_t *item = TAILQ_FIRST(&s->clients); item;
        item = TAILQ_NEXT(item, entries)) {
        client = item->client;
        if (client->is_connected == false || client->is_graphic == true)
            continue;
        live_time = client->live_time;
        sec_sus = (current.tv_sec - live_time.tv_sec);
        nsec_sus = (current.tv_nsec - live_time.tv_nsec);
        if (handle_client_death(client, s, sec_sus, nsec_sus) == true)
            return true;
    }
    return false;
}
