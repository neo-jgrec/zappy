/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenConnectNbrResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::listenConnectNbrResponse(const std::string &response)
{
    _state.slot = std::stoi(response);
}