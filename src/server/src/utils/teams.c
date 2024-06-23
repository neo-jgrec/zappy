/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** teams.c
*/

#include "server.h"

team_t *get_team_by_name(struct teams_tailq *teams, const char *team_name)
{
    team_list_t *item_t;

    if (team_name == NULL)
        return NULL;
    TAILQ_FOREACH(item_t, teams, entries) {
        if (strcmp(item_t->team->name, team_name) == 0)
            return item_t->team;
    }
    return NULL;
}

size_t team_nb_slots(struct teams_tailq *teams, const char *team_name)
{
    size_t counter = 0;
    bool team_found = false;

    if (team_name == NULL)
        return 0;
    for (team_list_t *item_t = TAILQ_FIRST(teams);
        item_t;
        item_t = TAILQ_NEXT(item_t, entries)) {
        if (strcmp(item_t->team->name, team_name) == 0)
            team_found = true;
        if (team_found == false)
            continue;
        for (eggs_list_t *item_e = TAILQ_FIRST(&item_t->team->eggs);
            item_e;
            item_e = TAILQ_NEXT(item_e, entries))
            counter++;
        break;
    }
    return counter;
}
