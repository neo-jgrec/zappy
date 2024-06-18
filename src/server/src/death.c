/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** death.c
*/

#include "server.h"

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
    }
    if (client->inventory.food == 0) {
        dprintf(client->fd, "dead\n");
        close(client->fd);
        FD_CLR(client->fd, &s->current_sockets);
        remove_client_by_fd(&s->clients, client->fd);
        message_to_graphicals(s, "pdi %d\n", client->fd);
        return true;
    }
    return false;
}

bool handle_client_life(server_t *s)
{
    client_list_t *item;
    struct timespec current = s->current_time;
    struct timespec live_time;
    client_t *client;
    time_t sec_sus;
    long nsec_sus;

    TAILQ_FOREACH(item, &s->clients, entries) {
        client = item->client;
        if (client->is_connected == false || client->is_graphic == true)
            continue;
        live_time = client->live_time;
        nsec_sus = (current.tv_nsec - live_time.tv_nsec);
        sec_sus = nsec_sus < 0 ? (current.tv_sec - live_time.tv_sec) - 1 :
        (current.tv_sec - live_time.tv_sec);
        nsec_sus += nsec_sus < 0 ? NANOSECONDS_IN_SECOND : 0;
        if (handle_client_death(client, s, sec_sus, nsec_sus))
            return true;
    }
    return false;
}
