/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** main
*/

#include <iostream>
#include <sstream>
#include <string>
#include <variant>
#include <vector>

#include "serverConnect.hpp"
#include "guiException.hpp"
#include "data.hpp"
#include "parser.hpp"

#include <boost/filesystem.hpp>
#include <boost/tokenizer.hpp>

#include "utils/Debug.hpp"

int main() {
    debug_print("Starting GUI");
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

    Data gameData;
    Parser parser;

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

        std::istringstream dataStream(data);
        std::string line;

        while (std::getline(dataStream, line)) {
            boost::tokenizer<> tok(line);
            std::vector<std::string> tokens(tok.begin(), tok.end());
            std::vector<std::variant<std::string, int>> vals;

            for (auto& token : tokens) {
                try {
                    int numVal = std::stoi(token);
                    vals.push_back(numVal);
                } catch (const std::exception& e) {
                    vals.push_back(token);
                }
            }
            parser.parse(vals, gameData);
            
            
            // if (tokens.at(0).compare("plv") == 0) {
            //     gameData.getPlayerById(std::stoi(tokens.at(1))).setLvl(std::stoi(tokens.at(2)));
            //     continue;
            // }
            // if (tokens.at(0).compare("ppo") == 0) {
            //     gameData.getPlayerById(std::stoi(tokens.at(1))).update(tokens);
            //     continue;
            // }
            // if (tokens.at(0).compare("pin") == 0) {
            //     gameData.getPlayerById(std::stoi(tokens.at(1))).setInventory(tokens);
            //     continue;
            // }
        }
        parser.execute();
    }
    return 0;
}
