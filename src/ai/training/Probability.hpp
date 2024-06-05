/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Probability.hpp
*/

#ifndef PROBABILITY_HPP_
#define PROBABILITY_HPP_

#include <iostream>

class Probability
{
public:
    Probability(double condition, double probability, std::string name);
    ~Probability();

    double condition;
    double probability;
    std::string name;
};

#endif // PROBABILITY_HPP_
