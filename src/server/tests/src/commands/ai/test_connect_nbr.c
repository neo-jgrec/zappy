#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

void connect_nbr(client_t *client, server_t *server);

static server_t *init_test_server(int width, int height) {
    server_t *server = malloc(sizeof(server_t));
    server->proprieties.width = width;
    server->proprieties.height = height;
    server->map = calloc(width * height, sizeof(tile_t));
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->teams);
    return server;
}

static client_t *add_test_client(server_t *server, int x, int y, int level, char *team_name)
{
    client_t *client = malloc(sizeof(client_t));
    client->x = x;
    client->y = y;
    client->level = level;
    client->team_name = team_name;
    client_list_t *client_entry = malloc(sizeof(client_list_t));
    client_entry->client = client;
    TAILQ_INSERT_TAIL(&server->clients, client_entry, entries);
    return client;
}

Test(connect_nbr, test_connect_nbr)
{
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 1, "Team1");

    connect_nbr(client, server);

    cr_assert_eq(client->level, 1, "Client level should be 1 after connect_nbr");

    free(server->map);
    free(server);
}

Test(connect_nbr, test_connect_nbr_2)
{
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 2, "Team1");

    connect_nbr(client, server);

    cr_assert_eq(client->level, 2, "Client level should be 2 after connect_nbr");

    free(server->map);
    free(server);
}
