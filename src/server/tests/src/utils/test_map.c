#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "server.h"

void redirect_all_stdout(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

static void init_map(server_t *server, int width, int height)
{
    server->proprieties.width = width;
    server->proprieties.height = height;
    server->map = calloc(width * height, sizeof(tile_t));
    if (server->map == NULL) {
        perror("Failed to allocate memory for map");
        exit(ERROR_STATUS);
    }
}

static void destroy_map(server_t *server)
{
    int size = server->proprieties.width * server->proprieties.height;
    for (int i = 0; i < size; i++)
        free(server->map[i].objects);
    free(server->map);
}

Test(map, add_element_to_map) {
    server_t server;
    memset(&server, 0, sizeof(server_t));
    init_map(&server, 10, 10);

    add_element_to_map(&server, 5, 5, DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].objects[0], DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].num_objects, 1);

    destroy_map(&server);
}

Test(map, remove_element_from_map) {
    server_t server;
    memset(&server, 0, sizeof(server_t));
    init_map(&server, 10, 10);

    add_element_to_map(&server, 5, 5, DERAUMERE);
    add_element_to_map(&server, 5, 5, DERAUMERE);
    add_element_to_map(&server, 5, 5, DERAUMERE);
    add_element_to_map(&server, 5, 5, DERAUMERE);

    remove_element_from_map(&server, 5, 5, DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].num_objects, 3);

    remove_element_from_map(&server, 5, 5, DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].num_objects, 2);

    remove_element_from_map(&server, 5, 5, DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].num_objects, 1);

    remove_element_from_map(&server, 5, 5, DERAUMERE);
    cr_assert_eq(server.map[5 * server.proprieties.width + 5].num_objects, 0);

    destroy_map(&server);
}

Test(map, print_map, .init = redirect_all_stdout) {
    char expected[] = "0, 0, [], 1, 0, [], 2, 0, [], 3, 0, [], 4, 0, [], 5, 0, [], 6, 0, [], 7, 0, [], 8, 0, [], 9, 0, []\n"
"0, 1, [], 1, 1, [], 2, 1, [], 3, 1, [], 4, 1, [], 5, 1, [], 6, 1, [], 7, 1, [], 8, 1, [], 9, 1, []\n"
"0, 2, [], 1, 2, [], 2, 2, [], 3, 2, [], 4, 2, [], 5, 2, [], 6, 2, [], 7, 2, [], 8, 2, [], 9, 2, []\n"
"0, 3, [], 1, 3, [], 2, 3, [], 3, 3, [], 4, 3, [], 5, 3, [], 6, 3, [], 7, 3, [], 8, 3, [], 9, 3, []\n"
"0, 4, [], 1, 4, [], 2, 4, [], 3, 4, [], 4, 4, [], 5, 4, [], 6, 4, [], 7, 4, [], 8, 4, [], 9, 4, []\n"
"0, 5, [], 1, 5, [], 2, 5, [], 3, 5, [], 4, 5, [], 5, 5, [deraumere, deraumere, deraumere], 6, 5, [], 7, 5, [], 8, 5, [], 9, 5, []\n"
"0, 6, [], 1, 6, [], 2, 6, [], 3, 6, [], 4, 6, [], 5, 6, [], 6, 6, [], 7, 6, [], 8, 6, [], 9, 6, []\n"
"0, 7, [], 1, 7, [], 2, 7, [], 3, 7, [], 4, 7, [], 5, 7, [], 6, 7, [], 7, 7, [], 8, 7, [], 9, 7, []\n"
"0, 8, [], 1, 8, [], 2, 8, [], 3, 8, [], 4, 8, [], 5, 8, [], 6, 8, [], 7, 8, [], 8, 8, [], 9, 8, []\n"
"0, 9, [], 1, 9, [], 2, 9, [], 3, 9, [], 4, 9, [], 5, 9, [], 6, 9, [], 7, 9, [], 8, 9, [], 9, 9, []\n";

    server_t server;
    memset(&server, 0, sizeof(server_t));
    init_map(&server, 10, 10);

    add_element_to_map(&server, 5, 5, DERAUMERE);
    add_element_to_map(&server, 5, 5, DERAUMERE);
    add_element_to_map(&server, 5, 5, DERAUMERE);

    print_map(&server);
    cr_assert_stdout_eq_str(expected);
}
