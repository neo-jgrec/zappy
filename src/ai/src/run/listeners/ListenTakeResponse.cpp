/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenTakeResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

// TODO: find a cleaner way to do this
void ABotPattern::listenTakeResponse(const std::string &response)
{
    if (_state.lastAction.parameter == "food")
    {
        if (response == "ok")
        {
            _state.ressources.food += 1;
        }
    }
    else if (_state.lastAction.parameter == "linemate")
    {
        if (response == "ok")
        {
            _state.ressources.linemate += 1;
        }
    }
    else if (_state.lastAction.parameter == "deraumere")
    {
        if (response == "ok")
        {
            _state.ressources.deraumere += 1;
        }
    }
    else if (_state.lastAction.parameter == "sibur")
    {
        if (response == "ok")
        {
            _state.ressources.sibur += 1;
        }
    }
}
