/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenIncantationResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenIncantationResponse(const std::string &response)
{
    if (response == "Elevation underway")
    {
        _state.state = WAIT_FOR_SERVER_RESPONSE;
    }
}

void ABot::listenIncantationReturnResponse(const std::string &response)
{
    if (response.find("Current level") != std::string::npos)
    {
        _state.level++;
        _state.state = STANDARD;
    }
    if (response.find("ko") != std::string::npos || response.find("ko") != std::string::npos)
    {
        _state.state = STANDARD;
    }
}
