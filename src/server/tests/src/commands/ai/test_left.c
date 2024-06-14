#include <criterion/criterion.h>
#include "server.h"

Test(left, left_north)
{
    client_t client;
    server_t server;
    client.orientation = NORTH;

    left(&client, &server);

    cr_assert_eq(client.orientation, WEST, "Client orientation not set correctly");
    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
}

Test(left, left_west)
{
    client_t client;
    server_t server;
    client.orientation = WEST;

    left(&client, &server);

    cr_assert_eq(client.orientation, SOUTH, "Client orientation not set correctly");
    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
}

Test(left, left_south)
{
    client_t client;
    server_t server;
    client.orientation = SOUTH;

    left(&client, &server);

    cr_assert_eq(client.orientation, EAST, "Client orientation not set correctly");
    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
}

Test(left, left_east)
{
    client_t client;
    server_t server;
    client.orientation = EAST;

    left(&client, &server);

    cr_assert_eq(client.orientation, NORTH, "Client orientation not set correctly");
    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
}
