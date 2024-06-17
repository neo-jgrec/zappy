#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <criterion/redirect.h>
#include "client.h"
#include "server.h"

void incantation_callback_end_of_command(client_t *client, server_t *server);

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

server_t *init_test_server(int width, int height) {
    server_t *server = malloc(sizeof(server_t));
    server->proprieties.width = width;
    server->proprieties.height = height;
    server->map = calloc(width * height, sizeof(tile_t));
    TAILQ_INIT(&server->clients);
    TAILQ_INIT(&server->teams);
    return server;
}

client_t *add_test_client(server_t *server, int x, int y, int level, char *team_name)
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

void add_resource_to_tile(tile_t *tile, object_t resource) {
    tile->objects = realloc(tile->objects, (tile->num_objects + 1) * sizeof(object_t));
    tile->objects[tile->num_objects++] = resource;
}

Test(incantation, successful_incantation) {
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 1, "Team1");
    client_t *client2 = add_test_client(server, 0, 0, 1, "Team1");

    add_resource_to_tile(&server->map[0], LINEMATE);

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 2, "Client level should be 2 after successful incantation");
    cr_assert_eq(client2->level, 2, "Client level should be 2 after successful incantation");

    free(server->map);
    free(server);
}

Test(incantation, fail_due_to_lack_of_resources, .init = redirect_all_stdout) {
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 1, "Team1");
    client_t *client2 = add_test_client(server, 0, 0, 1, "Team1");

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 1, "Client level should remain 1 due to lack of resources");
    cr_assert_eq(client2->level, 1, "Client level should remain 1 due to lack of resources");

    free(server->map);
    free(server);
}

Test(incantation, fail_due_to_lack_of_players, .init = redirect_all_stdout) {
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 1, "Team1");

    add_resource_to_tile(&server->map[0], LINEMATE);

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 1, "Client level should remain 1 due to lack of players");

    free(server->map);
    free(server);
}

Test(incantation, fail_due_to_mismatched_levels, .init = redirect_all_stdout) {
    server_t *server = init_test_server(10, 10);
    client_t *client = add_test_client(server, 0, 0, 2, "Team1");
    client_t *client2 = add_test_client(server, 0, 0, 1, "Team1");

    add_resource_to_tile(&server->map[0], LINEMATE);
    add_resource_to_tile(&server->map[0], DERAUMERE);
    add_resource_to_tile(&server->map[0], SIBUR);

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 2, "Client level should remain 2 due to mismatched levels");
    cr_assert_eq(client2->level, 1, "Client level should remain 1 due to mismatched levels");

    free(server->map);
    free(server);
}
