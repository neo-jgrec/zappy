#include <criterion/criterion.h>
#include "server.h"

Test(take, basic) {
    client_t client;
    server_t server;
    client.inventory.food = 0;
    client.inventory.linemate = 0;
    client.inventory.deraumere = 0;
    client.inventory.sibur = 0;
    client.inventory.mendiane = 0;
    client.inventory.phiras = 0;
    client.inventory.thystame = 0;
    client.commands = malloc(sizeof(char *) * 2);
    client.commands[0] = strdup("take");
    client.commands[1] = "food";
    tile_t tile;
    tile.num_objects = 1;
    tile.objects = malloc(sizeof(object_t) * 1);
    tile.objects[0] = FOOD;
    server.map = malloc(sizeof(tile_t) * 1);
    server.map[0] = tile;

    take(&client, &server);
    cr_assert_eq(client.inventory.food, 1, "Client inventory not updated correctly");
    cr_assert_eq(server.map[0].num_objects, 0, "Tile objects not updated correctly");
}

Test(take, no_object) {
    client_t client;
    server_t server;
    client.inventory.food = 0;
    client.inventory.linemate = 0;
    client.inventory.deraumere = 0;
    client.inventory.sibur = 0;
    client.inventory.mendiane = 0;
    client.inventory.phiras = 0;
    client.inventory.thystame = 0;
    client.commands = malloc(sizeof(char *) * 2);
    client.commands[0] = strdup("take");
    client.commands[1] = "no_object";
    tile_t tile;
    tile.num_objects = 0;
    tile.objects = NULL;
    server.map = malloc(sizeof(tile_t) * 1);
    server.map[0] = tile;

    take(&client, &server);
    cr_assert_eq(client.inventory.food, 0, "Client inventory not updated correctly");
    cr_assert_eq(server.map[0].num_objects, 0, "Tile objects not updated correctly");
}

Test(take, multiple_objects) {
    client_t client;
    server_t server;
    client.inventory.food = 0;
    client.inventory.linemate = 0;
    client.inventory.deraumere = 0;
    client.inventory.sibur = 0;
    client.inventory.mendiane = 0;
    client.inventory.phiras = 0;
    client.inventory.thystame = 0;
    client.commands = malloc(sizeof(char *) * 2);
    client.commands[0] = strdup("take");
    client.commands[1] = "food";
    tile_t tile;
    tile.num_objects = 2;
    tile.objects = malloc(sizeof(object_t) * 2);
    tile.objects[0] = FOOD;
    tile.objects[1] = FOOD;
    server.map = malloc(sizeof(tile_t) * 1);
    server.map[0] = tile;

    take(&client, &server);
    cr_assert_eq(client.inventory.food, 1, "Client inventory not updated correctly");
    cr_assert_eq(server.map[0].num_objects, 1, "Tile objects not updated correctly");
    cr_assert_eq(server.map[0].objects[0], FOOD, "Tile objects not updated correctly");
}
