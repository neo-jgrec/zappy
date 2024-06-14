#include <criterion/criterion.h>
#include "server.h"
#include <string.h>

Test(broadcast, message_format_test) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 5;
    client.y = 5;
    client.level = 1;

    TAILQ_INIT(&server.clients);

    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        client_t *new_client = malloc(sizeof(client_t));
        new_client->x = 2;
        new_client->y = 2;
        new_client->level = 1;
        client_list_t *new_client_list = malloc(sizeof(client_list_t));
        new_client_list->client = new_client;
        TAILQ_INSERT_TAIL(&server.clients, new_client_list, entries);
    }

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    char message[] = "Broadcast Hello, world!";
    char expected[] = "message 2, Hello, world!\n";

    strcpy(client.message, message);
    broadcast(&client, &server);
    cr_assert_str_eq(client.payload, expected);
}
