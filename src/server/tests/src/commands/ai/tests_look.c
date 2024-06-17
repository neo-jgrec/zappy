#include <criterion/criterion.h>
#include "server.h"

Test(look, basic_test)
{
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;
    server.map = calloc(server.proprieties.height * server.proprieties.width, sizeof(tile_t));

    server.map[5].num_objects = 2;
    server.map[5].objects = malloc(sizeof(object_t) * 2);
    server.map[5].objects[0] = FOOD;
    server.map[5].objects[1] = LINEMATE;

    client_t client;
    client.x = 5;
    client.y = 5;
    client.level = 1;

    client_list_t *new_client = malloc(sizeof(client_list_t));
    new_client->client = &client;
    TAILQ_INIT(&server.clients);
    TAILQ_INSERT_TAIL(&server.clients, new_client, entries);

    look(&client, &server);

    cr_assert_str_eq(client.payload, "[ food linemate player,,,, ]\n");
}
