#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(send_message_to_graphicals, basic, .init = redirect_all_stdout)
{
    server_t server;
    client_t client;
    client.fd = 1;
    client.is_graphic = true;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("test");
    TAILQ_INIT(&server.clients);
    client_list_t *client_list = calloc(1, sizeof(client_list_t));
    client_list->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list, entries);
    message_to_graphicals(&server, "test");
    cr_assert_stdout_eq_str("test");
}
