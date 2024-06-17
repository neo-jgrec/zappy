/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** set.c
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

static void remove_element_from_inventory(client_t *c, object_t object)
{
    for (size_t i = 0; i < 7; i++) {
        if (object_handlers[i].type == object) {
            c->inventory.food = object == FOOD
                ? c->inventory.food - 1 : c->inventory.food;
            c->inventory.linemate = object == LINEMATE
                ? c->inventory.linemate - 1 : c->inventory.linemate;
            c->inventory.deraumere = object == DERAUMERE
                ? c->inventory.deraumere - 1 : c->inventory.deraumere;
            c->inventory.sibur = object == SIBUR
                ? c->inventory.sibur - 1 : c->inventory.sibur;
            c->inventory.mendiane = object == MENDIANE
                ? c->inventory.mendiane - 1 : c->inventory.mendiane;
            c->inventory.phiras = object == PHIRAS
                ? c->inventory.phiras - 1 : c->inventory.phiras;
            c->inventory.thystame = object == THYSTAME
                ? c->inventory.thystame - 1 : c->inventory.thystame;
        }
    }
}

static void add_element_to_tile(tile_t *tile, object_t object)
{
    tile->num_objects++;
    tile->objects = realloc(tile->objects,
    sizeof(object_t) * tile->num_objects);
    tile->objects[tile->num_objects - 1] = object;
}

void set(client_t *c, server_t *s)
{
    object_t o = -1;

    if (c->commands[1] == NULL) {
        dprintf(c->fd, "ko\n");
        return;
    }
    for (size_t i = 0; i < 7; i++) {
        if (strcmp(object_handlers[i].name, c->commands[1]) == 0) {
            o = object_handlers[i].type;
            break;
        }
    }
    if ((int)o != -1 && c->inventory.food != 0) {
        remove_element_from_inventory(c, FOOD);
        add_element_to_tile(&s->map[c->y * s->proprieties.width + c->x], o);
        asprintf(&c->payload, "ok\n");
        message_to_graphicals(s, "pdr %s %d\n", c->uuid, o);
        client_time_handler(c, SET);
    }
    dprintf(c->fd, "ko\n");
}
