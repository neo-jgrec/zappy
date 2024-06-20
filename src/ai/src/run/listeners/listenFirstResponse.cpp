/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenFirstResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::listenFirstResponse(const std::string &response)
{
    int slot;
    unsigned int x;
    unsigned int y;

    std::string modifiedInput = response;
    std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
    std::istringstream iss(modifiedInput);
    iss >> slot >> x >> y;

    _state.slot = slot;
    _state.widthMap = x;
    _state.heightMap = y;
}
