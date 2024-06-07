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
    #define NB_COMMANDS 12
    #include <stdlib.h>
    #include <stdio.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <sys/queue.h> // Include for TAILQ
    #include "flags.h"
    #include "utils.h"
    #include "client.h"

typedef struct client_list_s {
    client_t *client;
    TAILQ_ENTRY(client_list_s) entries;
} client_list_t;

TAILQ_HEAD(client_tailq, client_list_s);

typedef struct server_s {
    struct sockaddr_in info;
    int fd;
    fd_set current_sockets;
    fd_set ready_sockets;
    flags_t proprieties;
    socklen_t addrlen;
    struct client_tailq clients;
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
