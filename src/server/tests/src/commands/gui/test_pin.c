#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"
#include "uuid.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(pin, basics, .init = redirect_all_stdout)
{
    server_t server;
    client_t client;
    client.fd = 1;
    client.x = 1;
    client.y = 1;
    client.orientation = 1;
    uuid_t binuuid;
    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, client.uuid);
    client.commands = calloc(2, sizeof(char *));
    client.commands[0] = strdup("pin");
    client.commands[1] = strdup("1");
    TAILQ_INIT(&server.clients);
    client_list_t *client_list = calloc(1, sizeof(client_list_t));
    client_list->client = &client;
    TAILQ_INSERT_TAIL(&server.clients, client_list, entries);
    pin(&client, &server);
    char expected[2550];
    sprintf(expected, "pin %d %u %u %u %u %u %u %u %u %u\n",
        client.id, client.x, client.y,
        client.inventory.food,
        client.inventory.linemate,
        client.inventory.deraumere,
        client.inventory.sibur,
        client.inventory.mendiane,
        client.inventory.phiras,
        client.inventory.thystame
    );
    cr_assert_stdout_eq_str(expected);
}
