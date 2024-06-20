/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** client.h
*/

#ifndef ZAPPY_CLIENT_H
    #define ZAPPY_CLIENT_H
    #define BUFFER_SIZE 1024
    #define NB_REQUESTS_HANDLEABLE 10
    #define NB_COMMANDS_TO_SEND 11
    #define LAST_LEVEL 8
    #include <stdint.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <sys/queue.h>
    #include <time.h>
    #include <uuid/uuid.h>
    #include "utils.h"

enum Orientation {
    NORTH,
    SOUTH,
    WEST,
    EAST
};

typedef struct inventory_s {
    uint32_t food;
    uint32_t linemate;
    uint32_t deraumere;
    uint32_t sibur;
    uint32_t mendiane;
    uint32_t phiras;
    uint32_t thystame;
} inventory_t;

typedef struct tclient_s {
    bool available_request;
    struct timespec future_time;
    int command;
    char *payload;
} tclient_t;

typedef struct client_s {
    char uuid[37];
    int fd;
    char **commands;
    char message[BUFFER_SIZE];
    signed char x;
    signed char y;
    bool is_connected;
    char *team_name;
    unsigned char orientation;
    inventory_t inventory;
    tclient_t tclient[NB_REQUESTS_HANDLEABLE];
    struct timespec live_time;
    size_t level;
    char *payload;
    bool is_incanting;
    bool is_graphic;
    size_t egg_id;
} client_t;

typedef struct client_list_s {
    client_t *client;
    TAILQ_ENTRY(client_list_s) entries;
} client_list_t;

/* LISTS */


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


/**
 * @brief Send a bufferized response to the client
 *
 * @param dest destination of the response
 * @param fmt format of the response
 * @param ... arguments to format
 *
 * @note the __attribute__((format(printf, 2, 3)))
 * is used to check the format params
 */
void handle_response(char **dest, const char *fmt, ...)
__attribute__((format(printf, 2, 3)));
#endif //ZAPPY_CLIENT_H
