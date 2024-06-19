/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ServerConnect
*/

#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <vector>

#include "ServerConnect.hpp"
#include "../utils/GuiException.hpp"
#include "../utils/Debug.hpp"

void ServerConnect::connectToServer(int port, const char *ip)
{
    // debug_print("\nConnecting to server", "");
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (this->fd < 0) {
        throw guiException("Failed to create a socket");
    }

    select.addFd(this->fd);
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, ip, &server_addr.sin_addr) <= 0) {
        throw guiException("Invalid address");
    }
    if (connect(this->fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        throw guiException("Failed to connect to the server");
    }
    // debug_print("\nConnected to server", "");
}

std::string ServerConnect::readFromServer()
{
    std::string message;
    std::vector<char> buffer(1024);
    int valread;

    if (select.select() > 0 && select.isSet(fd)) {
        // debug_print("\reading from server", "");
        while ((valread = read(this->fd, buffer.data(), buffer.size())) > 0) {
            message += std::string(buffer.data(), valread);
            if (message.back() == '\n' && valread != static_cast<int>(buffer.size()))
                break;
        }
        if (valread < 0)
            throw guiException("Failed to read from the server");
    }
    return message;
}

void ServerConnect::sendToServer(std::string message)
{
    if (write(this->fd, message.c_str(), message.size()) < 0) {
        throw guiException("Failed to send message to the server");
    }
    std::cout << "Sent: " << message << std::endl;
}
