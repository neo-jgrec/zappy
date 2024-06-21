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
