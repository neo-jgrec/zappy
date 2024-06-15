#include <criterion/criterion.h>
#include "server.h"

Test(right, basic) {
    client_t client;
    server_t server;
    client.orientation = NORTH;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, EAST, "Client orientation not changed correctly");
}

Test(right, east) {
    client_t client;
    server_t server;
    client.orientation = EAST;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, SOUTH, "Client orientation not changed correctly");
}

Test(right, south) {
    client_t client;
    server_t server;
    client.orientation = SOUTH;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, WEST, "Client orientation not changed correctly");
}

Test(right, west) {
    client_t client;
    server_t server;
    client.orientation = WEST;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, NORTH, "Client orientation not changed correctly");
}

Test(right, north) {
    client_t client;
    server_t server;
    client.orientation = NORTH;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, EAST, "Client orientation not changed correctly");
}

Test(right, east_wrap) {
    client_t client;
    server_t server;
    client.orientation = EAST;

    right(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.orientation, SOUTH, "Client orientation not changed correctly");
}
