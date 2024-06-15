/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** utils.h
*/


#ifndef ZAPPY_UTILS_H
    #define ZAPPY_UTILS_H
    #include <stdbool.h>
    #include <string.h>
    #include <stdio.h>
    #include <stdlib.h>

    #define _2D_ARRAY_TO_1D(array, x, y) (array)[(x) * (y) + (x)]

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
 * @param array array to free
 */
void free_array(void **array);


/**
 *
 * @param array array to get the length
 * @return length of the array
 */
size_t array_len(void **array);


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

/**
 *
 * @param str string to split
 * @param separator characters that will be used to split the string
 * @return
 */
char **str_to_array_separator(char const *str, char *separator);

#endif //ZAPPY_UTILS_H
