#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(handle_client_message, null_client_message, .init = redirect_all_std) {
    server_t server;
    server.clients.tqh_first = NULL;
    server.clients.tqh_last = &server.clients.tqh_first;
    client_t client;
    handle_client_message(&client, &server);
}

Test(handle_client_message, empty_client_message, .init = redirect_all_std) {
    server_t server;
    client_t client;
    strcpy(client.message, "");
    client.commands = NULL;
    client.fd = 1;
    client_list_t item;
    item.client = &client;
    TAILQ_INIT(&server.clients);
    TAILQ_INSERT_TAIL(&server.clients, &item, entries);
    handle_client_message(&client, &server);
}

Test(handle_client_message, unknown_command, .init = redirect_all_std) {
    server_t server;
    client_t client;
    strcpy(client.message, "Unknown");
    client.commands = NULL;
    client.fd = 1;
    client_list_t item;
    item.client = &client;
    TAILQ_INIT(&server.clients);
    TAILQ_INSERT_TAIL(&server.clients, &item, entries);
    handle_client_message(&client, &server);
}

Test(handle_client_message, valid_command, .init = redirect_all_std) {
    server_t server;
    client_t client;
    strcpy(client.message, "Forward");
    client.commands = NULL;
    client.fd = 1;
    client_list_t item;
    item.client = &client;
    TAILQ_INIT(&server.clients);
    TAILQ_INSERT_TAIL(&server.clients, &item, entries);
    handle_client_message(&client, &server);
}
