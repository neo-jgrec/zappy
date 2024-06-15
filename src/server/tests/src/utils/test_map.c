#include <criterion/criterion.h>
#include "server.h"
#include <string.h>

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
