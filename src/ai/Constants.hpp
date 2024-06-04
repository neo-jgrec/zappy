/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Constants.hpp
*/

#ifndef CONSTANTS_HPP_
#define CONSTANTS_HPP_

#include <array>

const std::array<std::array<int, 6>, 9> levelRequirements = {{
    {0, 0, 0, 0, 0, 0}, // Level 0
    {0, 0, 0, 0, 0, 0}, // Level 1
    {1, 0, 0, 0, 0, 0}, // Level 2
    {1, 1, 1, 0, 0, 0}, // Level 3
    {2, 0, 1, 0, 2, 0}, // Level 4
    {1, 1, 2, 0, 1, 0}, // Level 5
    {1, 2, 1, 3, 0, 0}, // Level 6
    {1, 2, 3, 0, 1, 0}, // Level 7
    {2, 2, 2, 2, 2, 1}  // Level 8
}};

#define PRINT_ERROR(errorMsg) std::cerr << "\033[31mError: " << errorMsg << " occurred in file " << __FILE__ << " at line " << __LINE__ << "\033[0m" << std::endl;

#endif // CONSTANTS_HPP_