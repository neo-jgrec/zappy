/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** broadcast.c
*/

#include "server.h"
#include <math.h>

static double adjust_angle_receiver_rotation(client_t *receiver, int angle)
{
    switch (receiver->orientation) {
        case NORTH:
            angle = fmod(angle + 360, 360);
            break;
        case EAST:
            angle = fmod(angle + 90, 360);
            break;
        case SOUTH:
            angle = fmod(angle + 180, 360);
            break;
        case WEST:
            angle = fmod(angle + 270, 360);
            break;
    }
    return angle;
}

static int get_sound_direction(
    client_t *sender,
    client_t *receiver,
    int map_width,
    int map_height
)
{
    int dx = sender->x - receiver->x;
    int dy = sender->y - receiver->y;
    double angle;
    const int direction_lookup[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    if (abs(dx) > map_width / 2)
        dx = (dx > 0) ? dx - map_width : dx + map_width;
    if (abs(dy) > map_height / 2)
        dy = (dy > 0) ? dy - map_height : dy + map_height;
    angle = atan2(dy, dx) * 180 / M_PI;
    angle = adjust_angle_receiver_rotation(receiver, angle);
    for (int i = 0; i < 8; i++) {
        if ((angle >= 337.5 + i * 45 || angle < 22.5 + i * 45)
            && (i != 0 || angle >= 337.5))
            return direction_lookup[i];
    }
    return 0;
}

static void send_broadcast_to_graphicals(client_t *client, server_t *server)
{
    client_list_t *client_list_entry;
    client_t *receiver;

    if (server->proprieties.is_iteration == true &&
    strcmp(client->commands[1], "STOP") == 0)
        exit(OK_STATUS);
    TAILQ_FOREACH(client_list_entry, &server->clients, entries) {
        receiver = client_list_entry->client;
        if (receiver->is_graphic)
            dprintf(receiver->fd, "pbc %d %s\n",
                client->fd, client->commands[1]);
    }
}

void broadcast(client_t *client, server_t *server)
{
    client_list_t *client_list_entry;
    int d;
    client_t *receiver;

    TAILQ_FOREACH(client_list_entry, &server->clients, entries) {
        receiver = client_list_entry->client;
        if (receiver == client)
            continue;
        d = get_sound_direction(
            client,
            receiver,
            server->proprieties.width,
            server->proprieties.height
        );
        dprintf(receiver->fd, "message %d, %s\n", d, client->commands[1]);
    }
    handle_response(&client->payload, "ok\n");
    send_broadcast_to_graphicals(client, server);
    client_time_handler(client, BROADCAST);
}
