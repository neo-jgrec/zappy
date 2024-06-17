#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(msz, basic, .init = redirect_all_stdout)
{
    server_t server;
    server.proprieties.width = 10;
    server.proprieties.height = 10;
    client_t client;
    client.fd = 1;
    msz(&client, &server);
    cr_assert_stdout_eq_str("msz 10 10\n");
}
