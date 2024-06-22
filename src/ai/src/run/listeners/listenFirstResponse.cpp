/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenFirstResponse.cpp
*/

#include "../../client/Client.hpp"

// TODO: use it ?
void Client::listenFirstResponse(const std::string &response)
{
    int slot;
    unsigned int x;
    unsigned int y;

    std::string modifiedInput = response;
    std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
    std::istringstream iss(modifiedInput);
    iss >> slot >> x >> y;

    _slot = slot;
    _width = x;
    _height = y;
}
