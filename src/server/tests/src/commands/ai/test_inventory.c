#include <criterion/criterion.h>
#include "server.h"

Test(inventory, basic) {
    client_t client;
    server_t server;
    client.inventory.food = 1;
    client.inventory.linemate = 2;
    client.inventory.deraumere = 3;
    client.inventory.sibur = 4;
    client.inventory.mendiane = 5;
    client.inventory.phiras = 6;
    client.inventory.thystame = 7;

    inventory(&client, &server);

    cr_assert_str_eq(client.payload, "[food 1, linemate 2, deraumere 3, sibur 4, mendiane 5, phiras 6, thystame 7]\n", "Client payload not set correctly");
}
