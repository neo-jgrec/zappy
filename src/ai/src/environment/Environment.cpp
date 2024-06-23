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
    std::unique_ptr<Tile> minDistanceTile = nullptr;
    int minDistance = std::numeric_limits<int>::max();

    for (const auto &tile : tiles)
    {
        bool hasResource = false;

        if (ressource == "food" && tile.ressources.food > 0)
            hasResource = true;
        else if (ressource == "linemate" && tile.ressources.linemate > 0)
            hasResource = true;
        else if (ressource == "deraumere" && tile.ressources.deraumere > 0)
            hasResource = true;
        else if (ressource == "sibur" && tile.ressources.sibur > 0)
            hasResource = true;
        else if (ressource == "mendiane" && tile.ressources.mendiane > 0)
            hasResource = true;
        else if (ressource == "phiras" && tile.ressources.phiras > 0)
            hasResource = true;
        else if (ressource == "thystame" && tile.ressources.thystame > 0)
            hasResource = true;

        if (hasResource && tile.distance < minDistance)
        {
            minDistance = tile.distance;
            minDistanceTile = std::make_unique<Tile>(tile);
        }
    }

    return minDistanceTile;
}
