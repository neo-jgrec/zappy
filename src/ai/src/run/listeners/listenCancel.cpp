/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenCancel(const std::string &response)
{
    PRINT_ALERT("listenCancel\n");
    if (response == "ko")
    {
        _state.state = STANDARD;
    }
}