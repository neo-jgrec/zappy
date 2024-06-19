/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenIncantationResponse.cpp
*/

#include "../../bots/ABotProbabilistic.hpp"

void ABotProbabilistic::listenIncantationResponse(const std::string &response)
{
    if (response == "Elevation underway")
    {
        _state.lastAction.action = LISTENING;
        _state.lastAction.parameter = "";
    }
}

void ABotProbabilistic::listenIncantationReturnResponse(const std::string &response)
{
    if (response.find("Current level") != std::string::npos)
    {
        _state.level++;
    }

    _state.lastAction.action = DEFAULT;
    _state.lastAction.parameter = "";
}
