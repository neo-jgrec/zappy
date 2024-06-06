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

        while (std::getline(dataStream, line)) {
            boost::tokenizer<> tok(line);
            std::vector<std::string> tokens(tok.begin(), tok.end());
            if (tokens.at(0).compare("msz") == 0) {
                if (gameData.getMap().getSize() > 0)
                    continue;
                gameData.getMap().fillMap(std::stoi(tokens.at(1)), std::stoi(tokens.at(2)));
                continue;
            }
            if (tokens.at(0).compare("bct") == 0) {
                gameData.getMap().updateTile(tokens);
                continue;
            }
            if (tokens.at(0).compare("enw") == 0) {
                gameData.addEgg(Egg(tokens));
                try {
                    gameData.getPlayerAt(std::stoi(tokens.at(1))).setEgging(false);
                } catch (const guiException& e) {}
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
            if (tokens.at(0).compare("pnw") == 0) {
                gameData.addPlayer(tokens);
                continue;
            }
            if (tokens.at(0).compare("pfk") == 0) {
                gameData.getPlayerAt(std::stoi(tokens.at(1))).setEgging(true);
                continue;
            }
            if (tokens.at(0).compare("pie") == 0) {
                std::vector<Player> pls = gameData.getPlayers();

                for (auto &pl : pls) {
                    if (pl.getPosition() == std::vector(std::stoi(tokens.at(1)), std::stoi(tokens.at(2)))) {
                        pl.setIncanting(false);
                        server.sendToServer("pie " + std::to_string(pl.getPlayerNb()) + "\n");
                    }
                }
                continue;
            }
            if (tokens.at(0).compare("plv") == 0) {
                gameData.getPlayerAt(std::stoi(tokens.at(1))).setLvl(std::stoi(tokens.at(2)));
                continue;
            }
            if (tokens.at(0).compare("pex") == 0) {
                // n | player n is pushing someone
            }
            if (tokens.at(0).compare("pie") == 0) {
                // X Y R | end of incantation on tile X Y with result R
            }
            if (tokens.at(0).compare("pic") == 0) {
                // X Y L n n n ... | start of incantation on tile X Y by players n n n ...
            }
            if (tokens.at(0).compare("pdr") == 0) {
                // n i | player n drops object i
            }
            if (tokens.at(0).compare("pgt") == 0) {
                // n i | player n takes object i
            }
            if (tokens.at(0).compare("pdi") == 0) {
                // n | death of a player
            }
            if (tokens.at(0).compare("ebo") == 0) {
                // e | egg e hatched
            }
            if (tokens.at(0).compare("edi") == 0) {
                // e | egg e died
            }
            if (tokens.at(0).compare("sgt") == 0) {
                gameData.setTickRate(std::stoi(tokens.at(1)));
                // T | get the time unit
            }
            if (tokens.at(0).compare("sst") == 0) {
                // T | set the time unit
            }
            if (tokens.at(0).compare("seg") == 0) {
                // N | team N won
            }
            if (tokens.at(0).compare("smg") == 0) {
                // M | server message M
            }
            if (tokens.at(0).compare("suc") == 0) {
                // unknown command
            }
            if (tokens.at(0).compare("sbp") == 0) {
                // command parameter
            }
            if (tokens.at(0).compare("ppo") == 0) {
                gameData.getPlayerAt(std::stoi(tokens.at(1))).update(tokens);
                continue;
            }
            if (tokens.at(0).compare("pin") == 0) {
                gameData.getPlayerAt(std::stoi(tokens.at(1))).setInventory(tokens);
                continue;
            }
            if (tokens.at(0).compare("pbc") == 0) {
                continue;
            }
            std::cout << line << std::endl;
        }
    }
    return 0;
}
