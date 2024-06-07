/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** client.h
*/

#ifndef ZAPPY_CLIENT_H
    #define ZAPPY_CLIENT_H
    #define BUFFER_SIZE 1024
    #include <stdlib.h>
    #include <stdio.h>
    #include "utils.h"

enum Orientation{
    NORTH,
    SOUTH,
    WEST,
    EAST
};

typedef struct inventory_s {

} inventory_t;

typedef struct client_s {
    char uuid[37];
    int fd;
    char **commands;
    char message[BUFFER_SIZE];
    struct client_s *next;
    struct client_s *prev;
    signed char x;
    signed char y;
    char *team_name;
    unsigned char orientation;
    inventory_t inventory;
} client_t;

/* LISTS */

/**
 *
 * @param clients clients to print
 */
void print_clients_fds(client_t *clients);

/**
 *
 * @param client_fd fd of the client
 * @return NULL if allocation failed either the client pointer
 */
client_t *init_client(int client_fd);


/**
 *
 * @param client list of clients to push
 * @param client_fd fd of the new client
 * @return false if allocation failed either true
 */
bool push_client(client_t *client, int client_fd);
#endif //ZAPPY_CLIENT_H
