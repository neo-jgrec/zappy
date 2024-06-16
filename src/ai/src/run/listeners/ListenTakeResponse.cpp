/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenTakeResponse.cpp
*/

#include "../../ABotProbabilistic.hpp"

// TODO: make others ressources
void ABotProbabilistic::listenTakeResponse(const std::string &response)
{
    if (_state.lastAction.parameter == "food")
    {
        if (response == "ok")
        {
            _state.ressources.food += 1;
        }
    }
}
