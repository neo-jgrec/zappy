#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(bct, basic, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.width = 10;
    server.proprieties.height = 10;
    server.map = calloc(server.proprieties.height * server.proprieties.width, sizeof(tile_t));
    client_t client;
    client.fd = 1;
    client.x = 5;
    client.y = 5;
    client.commands = calloc(3, sizeof(char *));
    client.commands[0] = strdup("bct");
    client.commands[1] = strdup("5");
    client.commands[2] = strdup("5");
    bct(&client, &server);
    cr_assert_stdout_eq_str("bct 5 5 0 0 0 0 0 0 0\n");
}

Test(bct, basic_with_food, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.width = 10;
    server.proprieties.height = 10;
    server.map = calloc(server.proprieties.height * server.proprieties.width, sizeof(tile_t));
    server.map[5 + 5 * server.proprieties.width].objects = calloc(1, sizeof(object_t));
    server.map[5 + 5 * server.proprieties.width].objects[0] = FOOD;
    server.map[5 + 5 * server.proprieties.width].num_objects = 1;
    client_t client;
    client.fd = 1;
    client.x = 5;
    client.y = 5;
    client.commands = calloc(3, sizeof(char *));
    client.commands[0] = strdup("bct");
    client.commands[1] = strdup("5");
    client.commands[2] = strdup("5");
    bct(&client, &server);
    cr_assert_stdout_eq_str("bct 5 5 1 0 0 0 0 0 0\n");
}

Test(bct, invalid_tile, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.width = 10;
    server.proprieties.height = 10;
    server.map = calloc(server.proprieties.height * server.proprieties.width, sizeof(tile_t));
    client_t client;
    client.fd = 1;
    client.x = 5;
    client.y = 5;
    client.commands = calloc(3, sizeof(char *));
    client.commands[0] = strdup("bct");
    client.commands[1] = strdup("10");
    client.commands[2] = strdup("10");
    bct(&client, &server);
    cr_assert_stdout_eq_str("sbp\n");
}

