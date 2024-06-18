#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

static void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(init_client, basic)
{
    client_t *client = init_client(1);
    cr_assert_not_null(client);
    cr_assert_eq(client->fd, 1);
    cr_assert_eq(client->is_graphic, false);
    free(client);
}

Test(destroy_clients, basic)
{
    struct client_tailq clients;
    TAILQ_INIT(&clients);

    client_t *client1 = init_client(1);
    client_t *client2 = init_client(2);
    client_list_t *item1 = malloc(sizeof(client_list_t));
    client_list_t *item2 = malloc(sizeof(client_list_t));
    item1->client = client1;
    item2->client = client2;
    TAILQ_INSERT_TAIL(&clients, item1, entries);
    TAILQ_INSERT_TAIL(&clients, item2, entries);

    destroy_clients(&clients);

    cr_assert(TAILQ_EMPTY(&clients));
}

Test(remove_client_by_fd, basic)
{
    struct client_tailq clients;
    TAILQ_INIT(&clients);

    client_t *client1 = init_client(1);
    client_t *client2 = init_client(2);
    client_list_t *item1 = malloc(sizeof(client_list_t));
    client_list_t *item2 = malloc(sizeof(client_list_t));
    item1->client = client1;
    item2->client = client2;
    TAILQ_INSERT_TAIL(&clients, item1, entries);
    TAILQ_INSERT_TAIL(&clients, item2, entries);

    remove_client_by_fd(&clients, 1);

    cr_assert_eq(TAILQ_FIRST(&clients)->client->fd, 2);
}

Test(print_clients_fds, basic, .init = redirect_all_stdout)
{
    struct client_tailq clients;
    TAILQ_INIT(&clients);

    client_t *client1 = init_client(1);
    client_t *client2 = init_client(2);
    client_list_t *item1 = malloc(sizeof(client_list_t));
    client_list_t *item2 = malloc(sizeof(client_list_t));
    item1->client = client1;
    item2->client = client2;
    TAILQ_INSERT_TAIL(&clients, item1, entries);
    TAILQ_INSERT_TAIL(&clients, item2, entries);

    print_clients_fds(&clients);
}
