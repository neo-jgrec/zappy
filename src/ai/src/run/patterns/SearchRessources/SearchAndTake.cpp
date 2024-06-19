/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../../bots/ABotProbabilistic.hpp"
#include "../../../constant/Constants.hpp"
#include <functional>

void ABotProbabilistic::searchAndTakeRessource(const std::string &ressource)
{
    if (_state.environment.tiles.empty())
    {
        queue.push_back({[&]()
                         { doAction(LOOK, ""); }, "LOOK"});
    }

    std::unordered_map<std::string, std::function<void()>> actions = {
        {"FORWARD", [&]()
         { doAction(FORWARD, ""); }},
        {"LEFT", [&]()
         { doAction(LEFT, ""); }},
        {"RIGHT", [&]()
         { doAction(RIGHT, ""); }},
        {"TAKE", [=]()
         { doAction(TAKE, ressource); }}};

    bool resourceFound = false;

    for (const auto &tile : _state.environment.tiles)
    {
        std::cout << "Tile: " << tile.x << " " << tile.y << std::endl;

        int resourceQuantity = 0;
        if (ressource == "food")
            resourceQuantity = tile.ressources.food;
        else if (ressource == "linemate")
            resourceQuantity = tile.ressources.linemate;
        else if (ressource == "deraumere")
            resourceQuantity = tile.ressources.deraumere;
        else if (ressource == "sibur")
            resourceQuantity = tile.ressources.sibur;
        else if (ressource == "mendiane")
            resourceQuantity = tile.ressources.mendiane;
        else if (ressource == "phiras")
            resourceQuantity = tile.ressources.phiras;
        else if (ressource == "thystame")
            resourceQuantity = tile.ressources.thystame;

        std::cout << ressource << ": " << resourceQuantity << std::endl;
        std::cout << "distance: " << tile.distance << std::endl;

        if (resourceQuantity > 0)
        {
            resourceFound = true;
            std::pair<int, int> coord = {tile.x, tile.y};
            if (movementMap.find(coord) != movementMap.end())
            {
                for (const auto &move : movementMap[coord])
                {
                    queue.push_back({actions[move], move});
                }
            }
            queue.push_back({actions["TAKE"], "TAKE"});
            break;
        }
    }

    if (!resourceFound)
        queue.push_back({[&]()
                         { doAction(FORWARD, ""); }, "FORWARD"});

    queue.push_back({[&]()
                     { doAction(LOOK, ""); }, "LOOK"});
}