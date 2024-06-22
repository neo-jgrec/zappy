/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Pattern.hpp
*/

#ifndef Pattern_HPP_
#define Pattern_HPP_

#include <functional>
#include <iostream>

class Pattern
{
public:
    Pattern(std::function<void()> act, std::string name);
    ~Pattern();

    std::function<void()> act;
    std::string name;
    unsigned int count = 0;
};

#endif // Pattern_HPP_
