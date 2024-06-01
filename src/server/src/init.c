/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** init.c
*/

#include <server.h>

static struct sockaddr_in init_socket_address(size_t port)
{
    struct sockaddr_in info;

    memset(&info, 0, sizeof(info));
    info.sin_family = AF_INET;
    info.sin_port = htons(port);
    info.sin_addr.s_addr = htonl(INADDR_ANY);
    return info;
}

bool init_server(server_t *server, const char **args)
{
    if (!init_flags(&server->proprieties, args))
        return false;
    server->clients = NULL;
    server->info = init_socket_address((size_t)server->proprieties.port);
    server->fd = socket(AF_INET, SOCK_STREAM, 0);
    server->addrlen = sizeof(struct sockaddr_in);
    if (server->fd < 0) {
        return false;
    }
    FD_ZERO(&server->current_sockets);
    FD_SET(server->fd, &server->current_sockets);
    return true;
}
