/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Behaviors.hpp
*/

#ifndef BEHAVIORS_HPP_
#define BEHAVIORS_HPP_

#include <iostream>
#include <functional>

class Behavior
{
public:
    Behavior(double probability, std::function<void()> act, std::string name);
    ~Behavior();

    double probability;
    std::function<void()> act;
    std::string name;
    unsigned int count = 0;
};

#endif // BEHAVIORS_HPP_