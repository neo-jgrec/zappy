/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenLookResponse.cpp
*/

#include "../../bots/ABot.hpp"
// Landmark: 1. Push it.
void ABot::listenLookResponse(const std::string &response)
{
    // Remove brackets
    std::string cleanedResponse = response.substr(1, response.size() - 2);

    std::istringstream iss(cleanedResponse);
    std::string tileString;

    _state.environment.clear();

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
        if (nbTile != 0)
            x = nbTile - center;
        Tile tile(x, y, distance, ressources);
        // std::cout << "====================\n";
        // std::cout << "tile content = " << tileString << std::endl;
        // std::cout << "at tile x = " << x << " y = " << y << " distance = " << distance << std::endl;
        // std::cout << "nbTile = " << nbTile << std::endl;
        // std::cout << "center = " << center << std::endl;
        // std::cout << "====================\n";

        _state.environment.tiles.push_back(tile);
        if (nbTile == 0)
        {
            y += 1;
        }
        nbTile++;
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
    for (auto &tile : _state.environment.tiles)
    {
        printColor("Tile: x:" + std::to_string(tile.x) + " y: " + std::to_string(tile.y) + " distance: " + std::to_string(tile.distance) + "\n", BRIGHT_BLUE);
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
