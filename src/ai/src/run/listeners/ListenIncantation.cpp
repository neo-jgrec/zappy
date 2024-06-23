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
        _state.metadata["wait_incant"] = "false";
    }
    if (response.find("ko") != std::string::npos)
    {
        PRINT_ALERT("Incantation failed\n");
        _state.state = STANDARD;
        _state.metadata["should_incant"] = "false";
        _state.metadata["wait_incant"] = "false";
    }
    // TODO: remove it
    if (_state.level == 8)
    {
        printColor("👑 WIN 👑", BRIGHT_GREEN);
        exit(0);
    }
}
