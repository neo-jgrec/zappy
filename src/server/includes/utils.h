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
int helper(int status);

/**
 * @param str string to check if it's numeric or not
 * @return returns a boolean
 */
bool str_is_num(const char *str);

/**
 *
 * @param array array to print
 */
void print_string_array(char **array);

/**
 *
 * @param elem elem to free
 */
void secure_free(void *elem);
#endif //ZAPPY_UTILS_H
