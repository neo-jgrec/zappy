/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Tile.cpp
*/

#include "Tile.hpp"

Tile::Tile(int x, int y, unsigned int distance, Ressources ressources)
{
    this->x = x;
    this->y = y;
    this->distance = distance;
    this->ressources = ressources;
}

Tile::~Tile()
{
}
