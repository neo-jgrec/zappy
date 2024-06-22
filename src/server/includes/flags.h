/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** flags.h
*/

#ifndef ZAPPY_FLAGS_H
    #define ZAPPY_FLAGS_H
    #define NB_FLAGS 5
    #define INCORRECT_FLAG_VALUE (-1)
    #include "utils.h"
    #include <stdint.h>

enum {
    PORT,
    WIDTH,
    HEIGHT,
    NAME,
    CLIENT_NB,
    FREQ
};

typedef struct info_map_s {
    uint8_t food;
    uint8_t linemate;
    uint8_t deraumere;
    uint8_t sibur;
    uint8_t mendiane;
    uint8_t phiras;
    uint8_t thystame;
} info_map_t;

typedef struct flags_s {
    int port;
    int width;
    int height;
    char **names;
    int nb_clients;
    int frequency;
    info_map_t max_map;
    bool is_iteration;
} flags_t;

/**
 * @param flags flags to fill
 * @param args arguments to get the flags
 * @return boolean if there are the 6 required flags
 */
bool init_flags(flags_t *flags, const char **args);

/**
 *
 * @param flags destroy essentially the names
 */
void destroy_flags(flags_t *flags);

#endif //ZAPPY_FLAGS_H
