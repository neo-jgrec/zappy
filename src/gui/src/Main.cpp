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
#include "utils/CommandLineParser.hpp"

int main(int argc, char **argv) {
    debug_print("Starting GUI", "");

    CommandLineParser cmdParser(argc, argv);
    cmdParser.addOption("--ip", "-i", "The ip to connect to");
    cmdParser.addOption("--port", "-p", "The port to connect to");
    cmdParser.addOption("--help", "-h", "Display this help message");

    try {
        cmdParser.parse();
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }

    if (cmdParser.getOption("--help") != std::nullopt) {
        cmdParser.displayHelp(argv[0]);
        return 0;
    }

    serverConnect server;

    if (cmdParser.getOption("--ip") != std::nullopt)
        server.ip = *cmdParser.getOption("--ip");
    if (cmdParser.getOption("--port") != std::nullopt) {
        try {
            server.port = std::stoi(*cmdParser.getOption("--port"));
            if (server.port < 1 || server.port > 65535)
                throw std::invalid_argument("");
        } catch (const std::invalid_argument &e) {
            std::cerr << "Port must be a number between 1 and 65,535" << std::endl;
            return 84;
        }
    }

    try {
        server.connectToServer(server.port, server.ip.c_str());
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