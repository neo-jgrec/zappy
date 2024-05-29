/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Environement.hpp
*/

#ifndef ENVIRONEMENT_HPP_
#define ENVIRONEMENT_HPP_

#include "ressources/Ressources.hpp"

#include <iostream>
#include <vector>

// to verify: must have x y, should be an array
class Environement
{
public:
    Environement();
    ~Environement();
    std::vector<Ressources> ressources;

private:
};

#endif // ENVIRONEMENT_HPP_
