/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>
#include <raylib.h>

#include "serverConnect.hpp"


int main() {
    serverConnect server;
    try {
        server.connectToServer(3000, "127.0.0.1");
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to the server\n";
        return 1;
    }
    while (1) {
        std::string data;
        try {
            data = server.readFromServer();
        } catch (const std::exception& e) {
            std::cerr << "Failed to read from the server\n";
            return 1;
        }
        std::cout << data << std::endl;
    }
    return 0;
}
