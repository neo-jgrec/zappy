#include <criterion/criterion.h>
#include "server.h"

Test(forward, basic) {
    client_t client;
    server_t server;
    client.orientation = NORTH;
    client.x = 5;
    client.y = 5;
    server.proprieties.width = 10;
    server.proprieties.height = 10;

    forward(&client, &server);

    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.x, 5, "Client x-coordinate changed incorrectly");
    cr_assert_eq(client.y, 4, "Client y-coordinate not decremented as expected");
}

Test(forward, wrap_around) {
    client_t client;
    server_t server;
    client.orientation = SOUTH;
    client.x = 5;
    client.y = 9;
    server.proprieties.width = 10;
    server.proprieties.height = 10;

    forward(&client, &server);

    printf("client.x, client.y: %d, %d\n", client.x, client.y);
    cr_assert_str_eq(client.payload, "ok\n", "Client payload not set correctly");
    cr_assert_eq(client.x, 5, "Client x-coordinate changed incorrectly");
    cr_assert_eq(client.y, 0, "Client y-coordinate not incremented as expected");
}
