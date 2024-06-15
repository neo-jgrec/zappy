/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "serverConnect.hpp"
#include "guiException.hpp"
#include "core/core.hpp"

int main() {

    try {
        Core core;
        core.run();
    } catch (const guiException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;

    serverConnect server;
    try {
        server.connectToServer(3000, "127.0.0.1");
    } catch (const guiException& e) {
        std::cerr <<  e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    while (1) {
        std::string data;
        try {
            data = server.readFromServer();
        } catch (const guiException& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            return 1;
        }
        if (data.compare(std::string("WELCOME\n")) == 0) {
            server.sendToServer("GRAPHIC\n");
            continue;
        }
    }
    return 0;
}
