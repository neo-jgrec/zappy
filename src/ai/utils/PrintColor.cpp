/*
** EPITECH PROJECT, 2024
** zappy/ai/utils
** File description:
** PrintColor.cpp
*/

#include "PrintColor.hpp"

void printColor(const std::string &message, const std::string &color)
{
    std::cout << color << message << COLOR_RESET << std::endl;
}
