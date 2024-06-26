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
    #define PLAYER_LIFE_LIMIT 126.0f

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
    #define METEORS_LIMIT 20.0f
    #define NB_AI_COMMANDS 12
    #define NB_GUI_COMMANDS 9
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
    int x;
    int y;
    int id;
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
    size_t nb_eggs;
} team_t;

typedef struct team_list_s {
    team_t *team;
    TAILQ_ENTRY(team_list_s) entries;
} team_list_t;

typedef enum {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER,
    EMPTY
} object_t;

typedef struct {
    size_t num_objects;
    object_t *objects;
} tile_t;

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
    struct timespec meteor_last_time;
    struct timeval timeout;
    tile_t *map;
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
void execute_commands_ai(client_t *client, server_t *server);


/**
 * Handle meteors
 * @param server
 */
void handle_meteors(server_t *server);

/**
 * handle food and time units for the player
 * @param s
 * @return
 */
bool handle_client_life(server_t *s);

/**
 * returns the rand() % val, don't forger to srand(time(NULL))
 * @param val
 * @return
 */
int rand_p(int val);

/**
 * Check resources, if not equitable
 * @param server
 */
void check_available_resources(server_t *server);

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


/* commands ai */
void handle_client_message(client_t *client, server_t *server);
void broadcast(client_t *client, server_t *server);
void connect_nbr(client_t *client, server_t *server);
void eject(client_t *client, server_t *server);
void fork_z(client_t *client, server_t *server);
void forward(client_t *client, server_t *server);
void incantation(client_t *client, server_t *server);
void incantation_callback_end_of_command(client_t *client, server_t *server);
void callback_freeze(client_t *client, server_t *server);
void callback_level_up(client_t *client, server_t *server);
void callback_unfreeze(client_t *client, server_t *server);
void callback_start_incantation_set_payload(client_t *client,
    server_t *server);
void callback_end_incantation_set_payload(client_t *client, server_t *server);
void inventory(client_t *client, server_t *server);
void left(client_t *client, server_t *server);
void look(client_t *client, server_t *server);
void right(client_t *client, server_t *server);
void set(client_t *client, server_t *server);
void take(client_t *client, server_t *server);

/* commands gui */
void bct(client_t *client, server_t *server);
void mct(client_t *client, server_t *server);
void msz(client_t *client, server_t *server);
void pin(client_t *client, server_t *server);
void plv(client_t *client, server_t *server);
void ppo(client_t *client, server_t *server);
void sgt(client_t *client, server_t *server);
void sst(client_t *client, server_t *server);
void tna(client_t *client, server_t *server);

/* map utils */

/**
 * @brief Get the map density object
 *
 * @param server
 * @param x
 * @param y
 * @param object
 */
void add_element_to_map(server_t *server, int x, int y, object_t object);

/**
 * @brief Remove an element from the map
 *
 * @param server
 * @param x
 * @param y
 * @param object
 */
void remove_element_from_map(server_t *server, int x, int y, object_t object);

/**
 * @brief Get the map density object
 *
 * @param server
 * @param x
 * @param y
 * @return info_map_t
 */
info_map_t get_map_density(server_t *server);

/**
 * @brief
 *
 * @param server
 */
void print_map(server_t *server);

/**
 * @brief
 *
 * @param tile
 */
void print_tile(tile_t *tile);

/**
 * @brief Send a message to all graphical clients
 *
 * @param server
 * @param fmt
 * @param ...
 */
void message_to_graphicals(server_t *server, char *fmt, ...);

void send_start_incantation_to_graphicals(client_t *client, server_t *server);

#endif /* !SERVER_H_ */
