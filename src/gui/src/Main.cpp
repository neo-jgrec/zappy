/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>

#include "ServerConnect.hpp"
#include "Parser.hpp"
#include "GuiException.hpp"
#include "Data.hpp"

#include "utils/Debug.hpp"

int main() {
    debug_print("Starting GUI");
    serverConnect server;
    try {
        server.connectToServer(3000, "127.0.0.1");
    } catch (const guiException& e) {
        std::cerr <<  e.what() << std::endl;
        return 84;
    }

    Data gameData;
    Parser parser;

    while (1) {
        parser.updateData(gameData, server);
    }
    return 0;
}
