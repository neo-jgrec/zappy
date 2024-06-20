#include <criterion/criterion.h>
#include "server.h"
#include <criterion/redirect.h>
#include <string.h>

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(broadcast, message_format_test, .init = redirect_all_stdout) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 5;
    client.y = 5;
    client.level = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("Broadcast");
    client.commands[1] = strdup("Hello, world!");

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

    client_list_t *client2 = TAILQ_FIRST(&server.clients);
    client2->client->fd = 1;

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    broadcast(&client, &server);
    cr_assert_stdout_eq_str("message 2, Hello, world!\n");
}

Test(broadcast, from_east_to_west, .init = redirect_all_stdout) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 9;
    client.y = 5;
    client.level = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("Broadcast");
    client.commands[1] = strdup("Hello, world!");

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

    client_list_t *client2 = TAILQ_FIRST(&server.clients);
    client2->client->fd = 1;

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    broadcast(&client, &server);
    cr_assert_stdout_eq_str("message 4, Hello, world!\n");
}

Test(broadcast, from_west_to_east, .init = redirect_all_stdout) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 0;
    client.y = 5;
    client.level = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("Broadcast");
    client.commands[1] = strdup("Hello, world!");

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

    client_list_t *client2 = TAILQ_FIRST(&server.clients);
    client2->client->fd = 1;

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    broadcast(&client, &server);
    cr_assert_stdout_eq_str("message 4, Hello, world!\n");
}

Test(broadcast, from_north_to_south, .init = redirect_all_stdout) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 5;
    client.y = 0;
    client.level = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("Broadcast");
    client.commands[1] = strdup("Hello, world!");

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

    client_list_t *client2 = TAILQ_FIRST(&server.clients);
    client2->client->fd = 1;

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    broadcast(&client, &server);
    cr_assert_stdout_eq_str("message 8, Hello, world!\n");
}

Test(broadcast, from_south_to_north, .init = redirect_all_stdout) {
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 5;
    client.y = 9;
    client.level = 1;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("Broadcast");
    client.commands[1] = strdup("Hello, world!");

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

    client_list_t *client2 = TAILQ_FIRST(&server.clients);
    client2->client->fd = 1;

    client_list_t *client_list_entry;
    client_list_entry = malloc(sizeof(client_list_t));
    client_list_entry->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry, entries);

    broadcast(&client, &server);
    cr_assert_stdout_eq_str("message 8, Hello, world!\n");
}
