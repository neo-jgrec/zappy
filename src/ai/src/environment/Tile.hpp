/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Tile.hpp
*/

#ifndef TILE_HPP_
#define TILE_HPP_

#include "../ressources/Ressources.hpp"

class Tile
{
public:
    Tile(int x, int y, unsigned int distance, Ressources ressources);
    Tile();
    ~Tile();
    int x;
    int y;
    unsigned int distance;
    Ressources ressources;
};

#endif // TILE_HPP_
