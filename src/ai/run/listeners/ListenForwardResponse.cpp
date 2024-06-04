/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenForwardeResponse.cpp
*/

#include "../../Bot.hpp"

void Bot::listenForwardResponse(const std::string &response)
{
    if (response == "ok")
    {
        state.reward = 0.05;
    }
    else
    {
        state.reward = -0.05;
    }
}