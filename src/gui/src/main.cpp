/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>

#include "serverConnect.hpp"


int main() {
    try {
        serverConnect server(3000, "127.0.0.1");
        while (1) {
            try {
                std::string data = server.readFromServer();
                std::cout << data << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Failed to read from the server: " << e.what() << std::endl;
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to connect to the server\n";
        return 1;
    }
    return 0;
}
