#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "client.h"
#include "server.h"

static server_t *create_test_server(size_t width, size_t height)
{
    server_t *server = calloc(1, sizeof(server_t));
    server->proprieties.width = width;
    server->proprieties.height = height;
    server->map = calloc(width * height, sizeof(tile_t));
    TAILQ_INIT(&server->clients);
    return server;
}

static void destroy_test_server(server_t *server)
{
    free(server->map);
    free(server);
}

static client_t *create_test_client(server_t *server, size_t x, size_t y, size_t level, bool is_graphic)
{
    client_t *client = calloc(1, sizeof(client_t));
    client->x = x;
    client->y = y;
    client->level = level;
    client->is_graphic = is_graphic;
    client_list_t *client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = client;
    TAILQ_INSERT_TAIL(&server->clients, client_list_entry, entries);
    return client;
}

Test(incantation, test_successful_incantation)
{
    server_t *server = create_test_server(10, 10);
    client_t *client = create_test_client(server, 0, 0, 1, false);

    add_element_to_map(server, 0, 0, LINEMATE);

    incantation(client, server);

    cr_assert(client->is_incanting, "Incantation should be in progress.");
    cr_assert_eq(client->level, 1, "Client level should not change yet.");
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 2, "Client should level up.");

    destroy_test_server(server);
}

Test(incantation, test_failed_incantation_not_enough_players)
{
    server_t *server = create_test_server(10, 10);
    client_t *client = create_test_client(server, 0, 0, 2, false);

    add_element_to_map(server, 0, 0, LINEMATE);
    add_element_to_map(server, 0, 0, DERAUMERE);
    add_element_to_map(server, 0, 0, SIBUR);

    incantation(client, server);

    cr_assert_not(client->is_incanting, "Incantation should not be in progress.");
    cr_assert_eq(client->level, 2, "Client level should remain the same.");

    destroy_test_server(server);
}

Test(incantation, test_failed_incantation_not_enough_resources)
{
    server_t *server = create_test_server(10, 10);
    client_t *client = create_test_client(server, 0, 0, 2, false);
    client_t *client2 = create_test_client(server, 0, 0, 2, false);
    (void)client2;

    add_element_to_map(server, 0, 0, LINEMATE);

    incantation(client, server);

    cr_assert_not(client->is_incanting, "Incantation should not be in progress.");
    cr_assert_eq(client->level, 2, "Client level should remain the same.");

    destroy_test_server(server);
}

Test(incantation, test_level_up)
{
    server_t *server = create_test_server(10, 10);
    client_t *client = create_test_client(server, 0, 0, 2, false);
    client_t *client2 = create_test_client(server, 0, 0, 2, false);

    add_element_to_map(server, 0, 0, LINEMATE);
    add_element_to_map(server, 0, 0, DERAUMERE);
    add_element_to_map(server, 0, 0, SIBUR);

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 3, "Client should level up.");
    cr_assert_eq(client2->level, 3, "Client2 should level up.");

    destroy_test_server(server);
}

Test(incantation, test_high_level_incantation)
{
    server_t *server = create_test_server(10, 10);
    client_t *client = create_test_client(server, 0, 0, 7, false);
    client_t *client2 = create_test_client(server, 0, 0, 7, false);
    client_t *client3 = create_test_client(server, 0, 0, 7, false);
    client_t *client4 = create_test_client(server, 0, 0, 7, false);
    client_t *client5 = create_test_client(server, 0, 0, 7, false);
    client_t *client6 = create_test_client(server, 0, 0, 7, false);

    add_element_to_map(server, 0, 0, LINEMATE);
    add_element_to_map(server, 0, 0, LINEMATE);
    add_element_to_map(server, 0, 0, DERAUMERE);
    add_element_to_map(server, 0, 0, DERAUMERE);
    add_element_to_map(server, 0, 0, SIBUR);
    add_element_to_map(server, 0, 0, SIBUR);
    add_element_to_map(server, 0, 0, MENDIANE);
    add_element_to_map(server, 0, 0, MENDIANE);
    add_element_to_map(server, 0, 0, PHIRAS);
    add_element_to_map(server, 0, 0, PHIRAS);
    add_element_to_map(server, 0, 0, THYSTAME);

    incantation(client, server);
    incantation_callback_end_of_command(client, server);

    cr_assert_eq(client->level, 8, "Client should level up to the highest level.");
    cr_assert_eq(client2->level, 8, "Client2 should level up to the highest level.");
    cr_assert_eq(client3->level, 8, "Client3 should level up to the highest level.");
    cr_assert_eq(client4->level, 8, "Client4 should level up to the highest level.");
    cr_assert_eq(client5->level, 8, "Client5 should level up to the highest level.");
    cr_assert_eq(client6->level, 8, "Client6 should level up to the highest level.");

    destroy_test_server(server);
}
