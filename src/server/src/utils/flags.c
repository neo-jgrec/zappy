/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** flags.c
*/

#include "server.h"

static bool count_flags(size_t flags[NB_FLAGS])
{
    for (size_t i = 0; i < NB_FLAGS; i++) {
        if (flags[i] != 1) {
            return false;
        }
    }
    return true;
}

static void get_int(size_t *flag_count, int *flag, const char *next_line)
{
    (*flag_count)++;
    if (next_line != NULL && str_is_num(next_line)) {
        *flag = atoi(next_line);
    } else {
        *flag = INCORRECT_FLAG_VALUE;
    }
}

static size_t count_nb_names(char **args, size_t *idx)
{
    size_t nb_names = 0;

    (*idx)++;
    for (size_t i = *idx; args[i]; i++) {
        if (strlen(args[i]) == 2 && args[i][0] == '-')
            break;
        nb_names++;
    }
    return nb_names;
}

static void get_names(size_t *flag_count, flags_t *flags, char **args,
    size_t *idx)
{
    size_t nb_names = count_nb_names(args, idx);

    (*flag_count)++;
    if (nb_names == 0)
        return;
    flags->names = malloc(sizeof(char *) * (nb_names + 1));
    if (flags->names == NULL)
        return;
    flags->names[nb_names] = NULL;
    for (size_t i = 0; args[(*idx)]; (*idx)++) {
        flags->names[i] = malloc(sizeof(char *) * (strlen(args[(*idx)]) + 1));
        if (flags->names[i] == NULL)
            break;
        strcpy(flags->names[i], args[(*idx)]);
        if (strlen(args[(*idx) + 1]) == 2 && args[(*idx) + 1][0] == '-')
            break;
        i++;
    }
}

static void fill_flags(size_t f_count[NB_FLAGS], flags_t *f,
    char **av, size_t i)
{
    switch (av[i][1]) {
        case 'p':
            get_int(&f_count[PORT], &f->port, av[i + 1]);
            break;
        case 'x':
            get_int(&f_count[WIDTH], &f->width, av[i + 1]);
            break;
        case 'y':
            get_int(&f_count[HEIGHT], &f->height, av[i + 1]);
            break;
        case 'n':
            get_names(&f_count[NAME], f, av, &i);
            break;
        case 'c':
            get_int(&f_count[CLIENT_NB], &f->nb_clients, av[i + 1]);
            break;
        case 'f':
            get_int(&f_count[FREQ], &f->frequency, av[i + 1]);
            break;
    }
}

static bool check_number_flags(flags_t *flags, char **args)
{
    size_t flags_counter[NB_FLAGS] = {0};

    if (!args)
        return false;
    for (size_t i = 0; args[i]; i++) {
        if (strlen(args[i]) != 2 || args[i][0] != '-')
            continue;
        fill_flags(flags_counter, flags, args, i);
    }
    return count_flags(flags_counter);
}

void print_flags(flags_t *flags)
{
    printf("PORT: %d\n", flags->port);
    printf("WIDTH: %d\n", flags->width);
    printf("HEIGHT: %d\n", flags->height);
    printf("NAMES:\n");
    print_string_array(flags->names);
    printf("NUMBER CLIENTS: %d\n", flags->nb_clients);
    printf("FREQUENCY: %d\n", flags->frequency);
}

void destroy_flags(flags_t *flags)
{
    if (flags->names == NULL)
        return;
    for (size_t i = 0; flags->names[i] != NULL; i++) {
        secure_free(flags->names[i]);
    }
    free(flags->names);
}

bool init_flags(flags_t *flags, char **args)
{
    flags->names = NULL;
    if (!check_number_flags(flags, args))
        return false;
    if (flags->port < 0 || flags->names == NULL || flags->frequency < 0
        || flags->width < 0 || flags->height < 0 || flags->nb_clients < 0)
        return false;
    print_flags(flags);
    return true;
}
