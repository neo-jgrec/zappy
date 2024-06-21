/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Environment.cpp
*/

#include "Environment.hpp"

Environment::Environment()
{
}

Environment::~Environment()
{
}

void Environment::clear()
{
    tiles.clear();
}

// to verify: optimize it
bool Environment::contains(std::string ressource)
{
    if (ressource == "food")
    {
        for (auto &tile : tiles)
        {
            if (tile.ressources.food > 0)
                return true;
        }
    }

    return false;
}

unsigned int Environment::getDistance(std::string ressource)
{
    unsigned int distance = 0;

    if (ressource == "food")
    {
        for (auto &tile : tiles)
        {
            if (tile.ressources.food > 0)
            {
                distance = tile.distance;
                break;
            }
        }
    }

    return distance;
}

std::unique_ptr<Tile> Environment::getTileByRessource(const std::string &ressource)
{
    for (const auto &tile : tiles)
    {
        if (ressource == "food" && tile.ressources.food > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "linemate" && tile.ressources.linemate > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "deraumere" && tile.ressources.deraumere > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "sibur" && tile.ressources.sibur > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "mendiane" && tile.ressources.mendiane > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "phiras" && tile.ressources.phiras > 0)
            return std::make_unique<Tile>(tile);
        else if (ressource == "thystame" && tile.ressources.thystame > 0)
            return std::make_unique<Tile>(tile);
    }

    return nullptr;
}
