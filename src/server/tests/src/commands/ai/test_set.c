#include <criterion/criterion.h>
#include "server.h"

Test(set, basic) {
    client_t client;
    server_t server;
    client.inventory.food = 1;
    client.inventory.linemate = 1;
    client.inventory.deraumere = 1;
    client.inventory.sibur = 1;
    client.inventory.mendiane = 1;
    client.inventory.phiras = 1;
    client.inventory.thystame = 1;
    client.commands = malloc(sizeof(char *) * 2);
    client.commands[0] = strdup("set");
    client.commands[1] = "food";
    tile_t tile;
    tile.num_objects = 0;
    tile.objects = NULL;
    server.map = malloc(sizeof(tile_t) * 1);
    server.map[0] = tile;

    set(&client, &server);
    cr_assert_eq(client.inventory.food, 0, "Client inventory not updated correctly");
    cr_assert_eq(server.map[0].num_objects, 1, "Tile objects not updated correctly");
    cr_assert_eq(server.map[0].objects[0], FOOD, "Tile objects not updated correctly");
}

Test(set, no_object) {
    client_t client;
    server_t server;
    client.inventory.food = 1;
    client.inventory.linemate = 1;
    client.inventory.deraumere = 1;
    client.inventory.sibur = 1;
    client.inventory.mendiane = 1;
    client.inventory.phiras = 1;
    client.inventory.thystame = 1;
    client.commands = malloc(sizeof(char *) * 2);
    client.commands[0] = strdup("set");
    client.commands[1] = "no_object";
    tile_t tile;
    tile.num_objects = 0;
    tile.objects = NULL;
    server.map = malloc(sizeof(tile_t) * 1);
    server.map[0] = tile;

    set(&client, &server);
    cr_assert_eq(client.inventory.food, 1, "Client inventory not updated correctly");
    cr_assert_eq(server.map[0].num_objects, 0, "Tile objects not updated correctly");
}
