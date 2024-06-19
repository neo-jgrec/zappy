/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** PatternProbabilistic.hpp
*/

#ifndef PatternProbabilistic_HPP_
#define PatternProbabilistic_HPP_

#include <iostream>
#include <functional>

class PatternProbabilistic
{
public:
    PatternProbabilistic(double probability, std::function<void()> act, std::string name);
    ~PatternProbabilistic();

    double probability;
    std::function<void()> act;
    std::string name;
    unsigned int count = 0;
};

#endif // PatternProbabilistic_HPP_