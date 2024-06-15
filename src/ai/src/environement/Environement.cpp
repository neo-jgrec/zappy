/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Environement.cpp
*/

#include "Environement.hpp"

Environement::Environement()
{
}

Environement::~Environement()
{
}

void Environement::clear()
{
    tiles.clear();
}

// to verify: optimize it
bool Environement::contains(std::string ressource)
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

unsigned int Environement::getDistance(std::string ressource)
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
