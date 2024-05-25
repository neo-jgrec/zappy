/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils.h
*/


#ifndef ZAPPY_UTILS_H
    #define ZAPPY_UTILS_H
    #include <stdbool.h>

/**
 *
 * @param av
 * @param status
 * @return
 */
int helper(char **av, int status);

/**
 * @param str string to check if it's numeric or not
 * @return returns a boolean
 */
bool str_is_num(const char *str);
#endif //ZAPPY_UTILS_H
