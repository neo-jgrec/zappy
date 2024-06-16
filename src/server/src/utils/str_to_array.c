/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** str_to_array.c
*/

/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** str_to_array
*/

#include <stdlib.h>
#include <stdbool.h>

static bool is_separator(char c, char const *separator)
{
    if (separator == NULL)
        return false;
    for (size_t i = 0; separator[i]; i++) {
        if (separator[i] == c)
            return false;
    }
    return true;
}

static size_t my_cols_counter(char const *str, size_t i, char *separator)
{
    size_t word = 0;

    for (; str[i] != '\0' && !is_separator(str[i], separator); i++);
    for (; str[i] != '\0' && is_separator(str[i], separator); i++)
        word++;
    return word;
}

static size_t count_lines(char const *str, char *separator)
{
    size_t n = 0;

    for (size_t i = 0; str[i] != '\0'; i++) {
        if ((is_separator(str[i], separator))
            && (!is_separator(str[i + 1], separator)
                || str[i + 1] == '\0')) {
            n++;
        }
    }
    return (n);
}

static char *set_line(char const *str, size_t j, char *separator)
{
    size_t cols = my_cols_counter(str, j, separator);
    char *cpy = malloc(sizeof(char) * (cols + 1));

    if (!cpy)
        return NULL;
    cpy[cols] = '\0';
    return cpy;
}

char **str_to_array_separator(char const *str, char *separator)
{
    size_t lines = count_lines(str, separator);
    char **array = malloc(sizeof(char *) * (lines + 1));
    size_t k = 0;
    size_t j = 0;

    if (array == NULL || str == NULL)
        return NULL;
    for (size_t i = 0; i < lines; i++) {
        array[i] = set_line(str, j, separator);
        if (!array[i])
            return NULL;
        for (; str[j] != '\0' && (!is_separator(str[j], separator)); j++);
        for (; str[j] != '\0' && is_separator(str[j], separator); j++) {
            array[i][k] = str[j];
            k++;
        }
        k = 0;
    }
    array[lines] = NULL;
    return (array);
}
