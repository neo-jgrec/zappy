// test_lists.c

#include <criterion/criterion.h>
#include "server.h"

#ifndef MAX_CAPACITY_TEAM
#define MAX_CAPACITY_TEAM 10
#endif

Test(init_team, basic) {
    team_t *team = init_team("TestTeam", 5, 100, 100);

    cr_assert_not_null(team, "init_team returned NULL");
    cr_assert_str_eq(team->name, "TestTeam", "Team name is incorrect");
    cr_assert_eq(team->nb_eggs, 5, "Number of eggs is incorrect");
    cr_assert_eq(team->capacity, 0, "Team capacity should be 0");
    cr_assert_eq(team->is_complete, false, "Team should not be complete");

    eggs_list_t *egg;
    TAILQ_FOREACH(egg, &team->eggs, entries) {
        cr_assert_geq(egg->egg->x, 0, "Egg x coordinate is out of bounds");
        cr_assert_lt(egg->egg->x, 100, "Egg x coordinate is out of bounds");
        cr_assert_geq(egg->egg->y, 0, "Egg y coordinate is out of bounds");
        cr_assert_lt(egg->egg->y, 100, "Egg y coordinate is out of bounds");
    }

    free(team->name);
    free(team);
}

// Test the destroy_teams function
Test(destroy_teams, basic) {
    struct teams_tailq teams;
    TAILQ_INIT(&teams);

    team_list_t *team_item = malloc(sizeof(team_list_t));
    team_item->team = init_team("TestTeam", 5, 100, 100);
    TAILQ_INSERT_TAIL(&teams, team_item, entries);

    destroy_teams(&teams);

    cr_assert(TAILQ_EMPTY(&teams), "Teams list should be empty after destroy");
}

