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
    #include <string.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include "utils.h"
    #include "flags.h"

/**
 *
 * @param args arguments to start the server
 * @return OK_STATUS if all worked or ERROR_STATUS
 */
int server(char **args);

#endif /* !SERVER_H_ */
