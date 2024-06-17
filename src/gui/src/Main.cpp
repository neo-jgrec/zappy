/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>

#include "parser/ServerConnect.hpp"
#include "parser/Parser.hpp"
#include "parser/Data.hpp"
#include "render/core/Core.hpp"

#include "utils/Debug.hpp"
#include "utils/CommandLineParser.hpp"
#include "utils/GuiException.hpp"

int main(int argc, char **argv) {
    int port = 0;
    std::string ip = "";

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

    if (cmdParser.getOption("--ip") != std::nullopt)
        ip = *cmdParser.getOption("--ip");
    if (cmdParser.getOption("--port") != std::nullopt) {
        try {
            port = std::stoi(*cmdParser.getOption("--port"));
            if (port < 1 || port > 65535)
                throw std::invalid_argument("");
        } catch (const std::invalid_argument &e) {
            std::cerr << "Port must be a number between 1 and 65,535" << std::endl;
            return 84;
        }
    }

    try {
        debug_print("Starting GUI", "");
        Core core(port, ip);
        core.run();
    } catch (const guiException& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;



    ServerConnect server;

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
