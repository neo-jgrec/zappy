/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** DisplayHelp.hpp
*/

#include "StringUtils.hpp"

std::string getElementAfter(const std::string& input, char delimiter)
{
    std::istringstream iss(input);
    std::string token;
    
    while (std::getline(iss, token, delimiter)) {
        if (iss >> token) {
            return token;
        }
    }

    return "";
}
