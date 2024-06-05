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
#include "data.hpp"

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
        int i = 0;
        while (std::getline(dataStream, line)) {
            i++;
            boost::tokenizer<> tok(line);
            std::vector<std::string> tokens(tok.begin(), tok.end());
            if (tokens.at(0).compare("msz") == 0) {
                if (gameData.map.getSize() > 0)
                    continue;
                gameData.map.fillMap(std::stoi(tokens.at(1)), std::stoi(tokens.at(2)));
                continue;
            }
            if (tokens.at(0).compare("bct") == 0) {
                gameData.map.updateTile(tokens);
                continue;
            }
            if (tokens.at(0).compare("enw") == 0) {
                gameData.addEgg(Egg(tokens));
                continue;
            }
            if (tokens.at(0).compare("sgt") == 0) {
                gameData.setTickRate(std::stoi(tokens.at(1)));
                continue;
            }
            if (tokens.at(0).compare("tna") == 0) {
                gameData.addTeam(tokens.at(1));
                continue;
            }
            std::cout << line << std::endl;
        }
    }
    return 0;
}
