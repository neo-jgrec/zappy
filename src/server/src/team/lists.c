/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** lists.c
*/

#include "server.h"

team_t *init_team(const char *team_name)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return NULL;
    team->next = NULL;
    team->prev = NULL;
    team->capacity = 0;
    team->is_available = true;
    for (signed char i = 0; i < MAX_CAPACITY_TEAM; i++) {
        team->client_ids[i] = NULL;
    }
    return team;
}

void free_teams(team_t *teams)
{
    team_t *next_team;

    if (teams == NULL)
        return;
    for (; teams->prev; teams = teams->prev);
    while (teams) {
        next_team = teams->next;
        free(teams);
        teams = next_team;
    }
    teams = NULL;
}

void print_teams_infos(team_t *teams)
{
    char **uuids;
    unsigned char i = 0;

    for (; teams; teams = teams->next) {
        uuids = teams->client_ids;
        i = 0;
        printf("Team is %savailable\n", teams->is_available ? "" : "not ");
        printf("UUID:\n");
        for (; i < MAX_CAPACITY_TEAM && uuids[i] != NULL; i++) {
            printf("%u - (%s)\n", i, teams->client_ids[i]);
        }
    }
}

bool push_team(team_t *team, const char *team_name)
{
    team_t *new_team = init_team(team_name);

    if (new_team == NULL)
        return false;
    if (team == NULL) {
        team = new_team;
        return true;
    }
    for (; team->next; team = team->next);
    team->next = new_team;
    new_team->prev = team;
    return true;
}

void add_client_uuid_to_team(team_t *team, char uuid[37])
{
    unsigned char i = 0;

    for (; i < MAX_CAPACITY_TEAM; i++) {
        if (team->client_ids[i] == NULL) {
            team->client_ids[i] = uuid;
            break;
        }
    }
}
