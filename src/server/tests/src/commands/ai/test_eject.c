#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "client.h"
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(eject, basic, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.height = 10;
    server.proprieties.width = 10;

    client_t client;
    client.x = 5;
    client.y = 5;
    client.level = 1;
    client.id = 0;
    client.orientation = NORTH;

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

    client_t client2;
    client2.x = 5;
    client2.y = 5;
    client2.level = 1;
    client2.fd = 1;
    client2.id = 1;
    client2.orientation = NORTH;

    client_list_t *client_list_entry2;
    client_list_entry2 = malloc(sizeof(client_list_t));
    client_list_entry2->client = &client2;
    TAILQ_INSERT_TAIL(&server.clients, client_list_entry2, entries);

    eject(&client, &server);

    cr_assert_eq(client2.x, 5);
    cr_assert_eq(client2.y, 4);
    cr_assert_stdout_eq_str("eject: 3\n");

    cr_assert_str_eq(client.payload, "ok\n");
}
