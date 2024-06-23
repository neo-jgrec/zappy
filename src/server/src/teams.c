/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** lists.c
*/

#include "server.h"

static void *create_eggs(team_t *team, int nb_client, int width, int height)
{
    eggs_list_t *new_egg;

    for (int i = 0; i < nb_client; i++) {
        new_egg = malloc(sizeof(eggs_list_t));
        if (new_egg == NULL)
            return NULL;
        new_egg->egg = init_egg(width, height);
        TAILQ_INSERT_TAIL(&team->eggs, new_egg, entries);
        team->nb_eggs++;
    }
    return new_egg;
}

team_t *init_team(const char *team_name, int nb_client, int width, int height)
{
    team_t *team = malloc(sizeof(team_t));

    if (team == NULL)
        return NULL;
    team->capacity = 0;
    team->is_complete = false;
    team->nb_eggs = 0;
    for (unsigned char i = 0; i < MAX_CAPACITY_TEAM; i++)
        team->client_ids[i] = NULL;
    team->name = malloc(sizeof(char) * (strlen(team_name) + 1));
    strcpy(team->name, team_name);
    team->name[strlen(team_name)] = '\0';
    TAILQ_INIT(&team->eggs);
    if (create_eggs(team, nb_client, width, height) == NULL)
        return NULL;
    return team;
}

void destroy_teams(struct teams_tailq *teams)
{
    team_list_t *item;

    while (!TAILQ_EMPTY(teams)) {
        item = TAILQ_FIRST(teams);
        TAILQ_REMOVE(teams, item, entries);
        secure_free((void **)&item->team->name);
        secure_free((void **)&item->team);
    }
}

void print_teams_infos(struct teams_tailq *teams)
{
    char **uuids;
    unsigned char idx = 0;
    eggs_list_t *item_e;
    char *res;

    for (team_list_t *i = TAILQ_FIRST(teams); i; i = TAILQ_NEXT(i, entries)) {
        uuids = i->team->client_ids;
        idx = 0;
        res = i->team->is_complete ? "" : "not ";
        printf("Team %s is %scomplete\n", i->team->name, res);
        printf("UUIDs:\n");
        for (; idx < MAX_CAPACITY_TEAM && uuids[idx] != NULL; idx++)
            printf("%u - (%s)\n", idx, i->team->client_ids[idx]);
        printf("Eggs:\n");
        item_e = TAILQ_FIRST(&i->team->eggs);
        while (item_e != NULL) {
            printf("X(%u) Y(%u)\n", item_e->egg->x, item_e->egg->y);
            item_e = TAILQ_NEXT(item_e, entries);
        }
    }
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
