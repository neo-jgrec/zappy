/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** take.c
*/

#include "server.h"

static const struct {
    char *name;
    object_t type;
} object_handlers[] = {
    {"food", FOOD},
    {"linemate", LINEMATE},
    {"deraumere", DERAUMERE},
    {"sibur", SIBUR},
    {"mendiane", MENDIANE},
    {"phiras", PHIRAS},
    {"thystame", THYSTAME},
};

static void add_element_to_inventory(client_t *c, object_t object)
{
    for (size_t i = 0; i < 7; i++) {
        if (object_handlers[i].type == object) {
            c->inventory.food = object == FOOD
                ? c->inventory.food + 1 : c->inventory.food;
            c->inventory.linemate = object == LINEMATE
                ? c->inventory.linemate + 1 : c->inventory.linemate;
            c->inventory.deraumere = object == DERAUMERE
                ? c->inventory.deraumere + 1 : c->inventory.deraumere;
            c->inventory.sibur = object == SIBUR
                ? c->inventory.sibur + 1 : c->inventory.sibur;
            c->inventory.mendiane = object == MENDIANE
                ? c->inventory.mendiane + 1 : c->inventory.mendiane;
            c->inventory.phiras = object == PHIRAS
                ? c->inventory.phiras + 1 : c->inventory.phiras;
            c->inventory.thystame = object == THYSTAME
                ? c->inventory.thystame + 1 : c->inventory.thystame;
        }
    }
}

static bool does_object_exist_on_tile(tile_t *tile, object_t object)
{
    for (size_t i = 0; i < tile->num_objects; i++) {
        if (tile->objects[i] == object)
            return true;
    }
    return false;
}

static object_t get_object_from_string(char *object_string)
{
    object_t object = -1;

    for (size_t i = 0; i < 7; i++) {
        if (strcmp(object_handlers[i].name, object_string) == 0) {
            object = object_handlers[i].type;
            break;
        }
    }
    return object;
}

void take(client_t *client, server_t *s)
{
    tile_t *tile = &s->map[client->y * s->proprieties.width + client->x];
    object_t object;

    if (client->commands[1] == NULL) {
        dprintf(client->fd, "ko\n");
        return;
    }
    object = get_object_from_string(client->commands[1]);
    if ((int)object == -1 || object == PLAYER || object == EMPTY) {
        dprintf(client->fd, "ko\n");
        return;
    }
    if (does_object_exist_on_tile(tile, object)) {
        add_element_to_inventory(client, object);
        remove_element_from_map(s, client->x, client->y, object);
        asprintf(&client->payload, "ok\n");
        message_to_graphicals(s, "pgt %d %d\n", client->fd, object);
        client_time_handler(client, TAKE);
    } else
        dprintf(client->fd, "ko\n");
}
