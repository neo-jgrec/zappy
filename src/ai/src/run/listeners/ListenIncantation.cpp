/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenIncantationResponse.cpp
*/

#include "../../ABotProbabilistic.hpp"

void ABotProbabilistic::listenIncantationResponse(const std::string &response)
{
    if (response == "Elevation underway")
    {
        _state.level++;
    }
}
