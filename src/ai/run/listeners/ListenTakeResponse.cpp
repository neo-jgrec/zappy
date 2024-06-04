/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenTakeResponse.cpp
*/

#include "../../Bot.hpp"

// to verify: test reward
// We have to take a list of last actions and rewards them till a reward
void Bot::listenTakeResponse(const std::string &response)
{
    if (state.lastAction.parameter == "food")
    {
        if (response == "ok")
        {
            state.ressources.food += 1;
            state.reward = state.ressources.food * 0.05;
        }
        else
        {
            state.reward = -0.05;
        }
    }
}
