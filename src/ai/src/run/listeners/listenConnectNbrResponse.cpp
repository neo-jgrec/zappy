/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenConnectNbrResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::listenConnectNbrResponse(const std::string &response)
{
    try
    {
        _state.slot = std::stoi(response);
    }
    catch (std::invalid_argument &e)
    {
        PRINT_ERROR("Invalid argument error: " << e.what());
    }
    catch (std::out_of_range &e)
    {
        PRINT_ERROR("Out of range error: " << e.what());
    }
}
