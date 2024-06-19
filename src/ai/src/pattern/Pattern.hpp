/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Pattern.hpp
*/

#ifndef Pattern_HPP_
#define Pattern_HPP_

#include <iostream>
#include <functional>

class Pattern
{
public:
    Pattern(double probability, std::function<void()> act, std::string name);
    ~Pattern();

    double probability;
    std::function<void()> act;
    std::string name;
    unsigned int count = 0;
};

#endif // Pattern_HPP_