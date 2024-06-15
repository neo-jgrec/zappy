/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Environement.hpp
*/

#ifndef ENVIRONEMENT_HPP_
#define ENVIRONEMENT_HPP_

#include "Tile.hpp"

#include <iostream>
#include <vector>

// to verify: must have x y, should be an array

class Environement
{
public:
    Environement();
    ~Environement();
    std::vector<Tile> tiles;
    void clear();
    bool contains(std::string ressource);
    unsigned int getDistance(std::string ressource);
    // get coord (ressources)
};

#endif // ENVIRONEMENT_HPP_
