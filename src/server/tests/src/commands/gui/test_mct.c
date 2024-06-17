#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(mct, basic, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.width = 2;
    server.proprieties.height = 2;
    server.map = calloc(server.proprieties.height * server.proprieties.width, sizeof(tile_t));
    client_t client;
    client.fd = 1;
    client.x = 0;
    client.y = 0;
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("mct");
    mct(&client, &server);
    cr_assert_stdout_eq_str("bct 0 0 0 0 0 0 0 0 0\nbct 1 0 0 0 0 0 0 0 0\nbct 0 1 0 0 0 0 0 0 0\nbct 1 1 0 0 0 0 0 0 0\n");
}
