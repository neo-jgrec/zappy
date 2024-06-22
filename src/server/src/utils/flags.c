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

static size_t count_nb_names(const char **args, size_t *idx)
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

static void get_names(size_t *flag_count, flags_t *flags, const char **args,
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
        if (args[(*idx) + 1] != NULL && strlen(args[(*idx) + 1]) == 2
            && args[(*idx) + 1][0] == '-')
            break;
        i++;
    }
}

static void fill_flags(size_t f_count[NB_FLAGS], flags_t *f,
    const char **av, size_t i)
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

bool is_freq_flag(const char **args)
{
    for (size_t i = 0; args[i] != NULL; i++) {
        if (strcmp(args[i], "-f") == 0)
            return true;
    }
    return false;
}

static bool check_number_flags(flags_t *flags, const char **args)
{
    size_t flags_counter[NB_FLAGS] = {0};

    if (args == NULL)
        return false;
    flags->is_iteration = false;
    for (size_t i = 0; args[i]; i++) {
        if (strcmp(args[i], "--iteration") == 0)
            flags->is_iteration = true;
        if (strlen(args[i]) != 2 || args[i][0] != '-')
            continue;
        fill_flags(flags_counter, flags, args, i);
    }
    if (is_freq_flag(args) == false)
        flags->frequency = 100;
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
    if (flags == NULL)
        return;
    if (flags->names == NULL)
        return;
    for (size_t i = 0; flags->names[i] != NULL; i++) {
        secure_free((void**)&flags->names[i]);
    }
    free(flags->names);
}

static bool check_error_flags(flags_t *flags)
{
    if (flags->port < 0) {
        dprintf(2, "Invalid port\n");
        return false;
    } else if (flags->names == NULL) {
        dprintf(2, "Couldn't find any names\n");
        return false;
    }
    if (flags->frequency < 2 || flags->frequency > 10000) {
        dprintf(2, "Frequency can only be between 2 and 10000\n");
        return false;
    } else if (flags->width < 10 || flags->width > 1000 ||
            flags->height < 10 || flags->height > 1000) {
        dprintf(2, "Map values need to be between 10 and 1000\n");
        return false;
    }
    if (flags->nb_clients < 1 || flags->nb_clients > 200) {
        dprintf(2, "clientsNb can only be between 1 and 200\n");
        return false;
    }
    return true;
}

bool init_flags(flags_t *flags, const char **args)
{
    double width;
    double height;

    flags->names = NULL;
    if (!check_number_flags(flags, args) || !check_error_flags(flags))
        return false;
    width = (double)flags->width;
    height = (double)flags->height;
    flags->max_map.food = (int)(width * height * FOOD_DENSITY);
    flags->max_map.linemate = (int)(width * height * LINEMATE_DENSITY);
    flags->max_map.deraumere = (int)(width * height * DERAUMERE_DENSITY);
    flags->max_map.sibur = (int)(width * height * SIBUR_DENSITY);
    flags->max_map.mendiane = (int)(width * height * MENDIANE_DENSITY);
    flags->max_map.phiras = (int)(width * height * PHIRAS_DENSITY);
    flags->max_map.thystame = (int)(width * height * THYSTAME_DENSITY);
    return true;
}
