/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** server
*/

#ifndef SERVER_H_
    #define SERVER_H_
    #define ERROR_STATUS 84
    #define OK_STATUS 0
    #define FOOD_DENSITY 0.5f
    #define LINEMATE_DENSITY 0.3f
    #define DERAUMERE_DENSITY 0.15f
    #define SIBUR_DENSITY 0.1f
    #define MENDIANE_DENSITY 0.1f
    #define PHIRAS_DENSITY 0.08f
    #define THYSTAME_DENSITY 0.05f
    #define NB_COMMANDS 12
    #define MAX_CAPACITY_TEAM 200
    #include <stdlib.h>
    #include <stdio.h>
    #include <netinet/in.h>
    #include <uuid/uuid.h>
    #include <unistd.h>
    #include "flags.h"
    #include "utils.h"
    #include "client.h"

typedef struct eggs_s {
    unsigned char x;
    unsigned char y;
    struct eggs_s *next;
    struct eggs_s *prev;
} eggs_t;

typedef struct team_s {
    char *client_ids[MAX_CAPACITY_TEAM];
    bool is_available;
    unsigned char capacity;
    struct team_s *next;
    struct team_s *prev;
} team_t;

typedef struct server_s {
    struct sockaddr_in info;
    int fd;
    fd_set current_sockets;
    fd_set ready_sockets;
    flags_t proprieties;
    socklen_t addrlen;
    client_t *clients;
    team_t *teams;
} server_t;

typedef struct commands_s {
    char *name;
    void (*command)(client_t *client, server_t *server);
} commands_t;

/**
 *
 * @param args arguments to start the server
 * @return OK_STATUS if all worked or ERROR_STATUS
 */
int server(const char **args);

/**
 *
 * @param server server to init
 * @param args arguments of the program
 * @return true if succeed either false
 */
bool init_server(server_t *server, const char **args);

/**
 *
 * @param server server to free
 */
void destroy_server(server_t server);


/**
 * Create a new client
 * @param server
 * @return OK_STATUS if all worked or ERROR_STATUS
 */
int create_new_client(server_t *server);

/**
 *
 * @param server
 * @param client_fd
 * @return
 */
int handle_client_data(server_t *server, int client_fd);

/* commands */
void handle_client_message(server_t *server);
void broadcast(client_t *client, server_t *server);
void connect_nbr(client_t *client, server_t *server);
void connector(client_t *client, server_t *server);
void eject(client_t *client, server_t *server);
void fork_z(client_t *client, server_t *server);
void forward(client_t *client, server_t *server);
void incantation(client_t *client, server_t *server);
void inventory(client_t *client, server_t *server);
void left(client_t *client, server_t *server);
void look(client_t *client, server_t *server);
void right(client_t *client, server_t *server);
void set(client_t *client, server_t *server);
void take(client_t *client, server_t *server);
#endif /* !SERVER_H_ */
