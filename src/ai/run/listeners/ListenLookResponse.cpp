/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenLookResponse.cpp
*/

#include "../../Bot.hpp"

void Bot::listenLookResponse(const std::string &response)
{
    // Remove brackets
    std::string cleanedResponse = response.substr(1, response.size() - 2);

    std::istringstream iss(cleanedResponse);
    std::string tileString;

    state.environment.clear();

    int x = 0, y = 0;
    unsigned int distance = 0;
    unsigned int nbTile = 0;

    unsigned int center = 2;
    unsigned int limit = 4;
    unsigned int addCenter = 4;
    unsigned int addLimit = 5;

    while (std::getline(iss, tileString, ','))
    {
        std::istringstream tileStream(tileString);
        std::string item;

        Ressources ressources;

        while (tileStream >> item)
        {
            ressources.addRessource(item);
        }
        distance = abs(x) + abs(y);

        Tile tile(x, y, distance, ressources);
        state.environment.tiles.push_back(tile);
        if (nbTile == 0)
        {
            y += 1;
        }
        nbTile++;
        x = nbTile - center;
        if (nbTile == limit)
        {
            y++;
            center += addCenter;
            addCenter += 2;
            limit += addLimit;
            addLimit += 2;
        }
    }

    // debug
    for (auto &tile : state.environment.tiles)
    {
        std::cout << "Tile: x:" << tile.x << " y: " << tile.y << " distance: " << tile.distance << std::endl;
        std::cout << "Ressources: " << std::endl;
        std::cout << "food: " << tile.ressources.food << std::endl;
        std::cout << "linemate: " << tile.ressources.linemate << std::endl;
        std::cout << "deraumere: " << tile.ressources.deraumere << std::endl;
        std::cout << "sibur: " << tile.ressources.sibur << std::endl;
        std::cout << "mendiane: " << tile.ressources.mendiane << std::endl;
        std::cout << "phiras: " << tile.ressources.phiras << std::endl;
        std::cout << "thystame: " << tile.ressources.thystame << std::endl;
        std::cout << "player: " << tile.ressources.player << std::endl;
    }
}
