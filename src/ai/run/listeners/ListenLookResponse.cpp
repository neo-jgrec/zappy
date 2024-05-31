/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenLookResponse.cpp
*/

#include "../Bot.hpp"

void Bot::listenLookResponse(const std::string &response)
{
    // Remove brackets
    std::string cleanedResponse = response.substr(1, response.size() - 2);

    std::istringstream iss(cleanedResponse);
    std::string firstTile;
    std::getline(iss, firstTile, ',');

    // TODO: fix that
    // _environement.food = 0;
    // _environement.linemate = 0;
    // _environement.deraumere = 0;
    // _environement.sibur = 0;
    // _environement.mendiane = 0;
    // _environement.phiras = 0;
    // _environement.thystame = 0;
    // _environement.players = 0;

    // std::map<std::string, size_t &> itemMap = {
    //     {"food", _environement.food},
    //     {"linemate", _environement.linemate},
    //     {"deraumere", _environement.deraumere},
    //     {"sibur", _environement.sibur},
    //     {"mendiane", _environement.mendiane},
    //     {"phiras", _environement.phiras},
    //     {"thystame", _environement.thystame},
    //     {"player", _environement.players}};

    std::istringstream tileStream(firstTile);
    std::string item;

    // while (tileStream >> item)
    // {
    //     auto it = itemMap.find(item);
    //     if (it != itemMap.end())
    //     {
    //         it->second += 1;
    //     }
    // }
    // _shouldListen = false;
}