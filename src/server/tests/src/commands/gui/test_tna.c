#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void create_team(server_t *server, char *name)
{
    team_list_t *team = calloc(1, sizeof(team_list_t));
    team->team = calloc(1, sizeof(team_t));
    team->team->name = strdup(name);
    TAILQ_INSERT_TAIL(&server->teams, team, entries);
}

Test(tna, basics, .init = redirect_all_stdout)
{
    server_t server;
    TAILQ_INIT(&server.teams);
    create_team(&server, "team1");
    create_team(&server, "team2");
    client_t client;
    client.fd = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("tna");
    tna(&client, &server);
    cr_assert_stdout_eq_str("tna team1\ntna team2\n");
}
