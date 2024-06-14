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
    #define NEUTRAL_VALUE 1
    #define FOOD_DENSITY 0.5f
    #define LINEMATE_DENSITY 0.3f
    #define DERAUMERE_DENSITY 0.15f
    #define SIBUR_DENSITY 0.1f
    #define MENDIANE_DENSITY 0.1f
    #define PHIRAS_DENSITY 0.08f
    #define THYSTAME_DENSITY 0.05f
    #define NANOSECONDS_IN_SECOND 1.0e9

    // Time limits
    #define FORWARD_TLIMIT 7.0f
    #define RIGHT_TLIMIT 7.0f
    #define LEFT_TLIMIT 7.0f
    #define LOOK_TLIMIT 7.0f
    #define INVENTORY_TLIMIT 1.0f
    #define BROADCAST_TLIMIT 7.0f
    #define FORK_TLIMIT 42.0f
    #define EJECT_TLIMIT 7.0f
    #define TAKE_TLIMIT 7.0f
    #define SET_TLIMIT 7.0f
    #define INCANTATION_TLIMIT 300.0f
    #define NB_COMMANDS 12
    #define MAX_CAPACITY_TEAM 200
    #include <stdlib.h>
    #include <stdio.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include "flags.h"
    #include "utils.h"
    #include "client.h"

// Commands
enum Commands {
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION
};

TAILQ_HEAD(client_tailq, client_list_s);
TAILQ_HEAD(eggs_tailq, eggs_list_s);
TAILQ_HEAD(teams_tailq, team_list_s);

typedef struct egg_s {
    unsigned char x;
    unsigned char y;
} egg_t;

typedef struct eggs_list_s {
    egg_t *egg;
    TAILQ_ENTRY(eggs_list_s) entries;
} eggs_list_t;


typedef struct team_s {
    char *name;
    char *client_ids[MAX_CAPACITY_TEAM];
    bool is_complete;
    unsigned char capacity;
    struct eggs_tailq eggs;
} team_t;


typedef struct team_list_s {
    team_t *team;
    TAILQ_ENTRY(team_list_s) entries;
} team_list_t;


typedef struct server_s {
    struct sockaddr_in info;
    int fd;
    fd_set current_sockets;
    fd_set ready_sockets;
    flags_t proprieties;
    socklen_t addrlen;
    struct client_tailq clients;
    struct teams_tailq teams;
    struct timespec current_time;
    struct timeval timeout;
} server_t;

typedef struct interval_s {
    int command;
    double frequency;
} interval_t;

void print_clients_fds(struct client_tailq *clients);
void destroy_clients(struct client_tailq *clients);
void destroy_teams(struct teams_tailq *teams);
egg_t *init_egg(int width, int height);
team_t *init_team(const char *team_name, int nb_client, int width, int height);
void print_teams_infos(struct teams_tailq *teams);
void remove_client_by_fd(struct client_tailq *clients, int fd);

typedef struct commands_s {
    char *name;
    void (*command)(client_t *client, server_t *server);
} commands_t;

/**
 * Returns the size of the teams list
 * @param teams
 * @param team_name
 * @return
 */
size_t team_nb_slots(struct teams_tailq *teams, const char *team_name);

/**
 * Get a team by it's name
 * @param teams
 * @param team_name
 * @return
 */
team_t *get_team_by_name(struct teams_tailq *teams, const char *team_name);

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


/**
 * Handles the time when a client connects up to 10 (NB_REQUESTS_HANDLEABLE)
 * @param client client to handle
 * @param command command to copy
 */
void client_time_handler(client_t *client, int command);


/**
 * Handles client connection to a team
 * @param client
 * @param server
 * @return
 */
bool connector(client_t *client, server_t *server);


/* commands */
void handle_client_message(client_t *client, server_t *server);
void broadcast(client_t *client, server_t *server);
void connect_nbr(client_t *client, server_t *server);
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
