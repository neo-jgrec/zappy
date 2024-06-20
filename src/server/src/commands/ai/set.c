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

void set(client_t *c, server_t *s)
{
    object_t o = -1;

    if (c->commands[1] == NULL) {
        dprintf(c->fd, "ko\n");
        return;
    }
    if (c->tclient[NB_REQUESTS_HANDLEABLE - 1].available_request == true) {
        asprintf(&c->payload, "ko\n");
        client_time_handler(c, SET);
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
        add_element_to_map(s, c->x, c->y, o);
        asprintf(&c->payload, "ok\n");
        message_to_graphicals(s, "pdr %d %d\n", c->fd, o);
        client_time_handler(c, SET);
        return;
    }
    dprintf(c->fd, "ko\n");
}
