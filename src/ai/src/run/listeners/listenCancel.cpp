/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenCancel(const std::string &response)
{
    if (response == "ko")
    {
        PRINT_ALERT("listenCancel\n");
        _state.state = STANDARD;
    }
}