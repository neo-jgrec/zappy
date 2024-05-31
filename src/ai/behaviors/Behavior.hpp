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
    Behavior(double probability, std::function<void()> act, std::string name) : probability(probability), act(act), name(name){};
    ~Behavior(){};

    double probability;
    std::function<void()> act;
    std::string name;
};

#endif // BEHAVIORS_HPP_