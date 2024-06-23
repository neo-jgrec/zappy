/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Environment.hpp
*/

#ifndef Environment_HPP_
#define Environment_HPP_

#include "Tile.hpp"

#include <iostream>
#include <vector>
#include <memory>
#include <limits>

class Environment
{
public:
    Environment();
    ~Environment();
    std::vector<Tile> tiles;

    void clear();
    bool contains(std::string ressource);
    unsigned int getDistance(std::string ressource);
    std::unique_ptr<Tile> getTileByRessource(const std::string &ressource);
    // get coord (ressources)
};

#endif // Environment_HPP_
