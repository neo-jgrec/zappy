/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** flags.h
*/

#ifndef ZAPPY_FLAGS_H
    #define ZAPPY_FLAGS_H
    #define NB_FLAGS 6

enum {
    PORT,
    WIDTH,
    HEIGHT,
    NAME,
    CLIENT_NB,
    FREQ
};

/**
 *
 * @param args arguments to get the flags
 * @return boolean if there are the 6 required flags
 */
bool check_number_flags(char **args);

#endif //ZAPPY_FLAGS_H
