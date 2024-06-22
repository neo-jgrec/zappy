/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenGroup(const std::string &message)
{
    if (_state.metadata["should_group"] != "true") // TODO: rename it in process_group ?
    {
        try
        {
            std::string lastChar(1, message.back());
            unsigned int askLevel = std::stoi(lastChar);

            if (_state.level + 1 == askLevel)
            {
                queue.clear();
                _state.metadata["should_group"] = "true";
                _state.state = ACT_ON_BROADCAST;
            }
        }
        catch (std::invalid_argument &e)
        {
            PRINT_ERROR(e.what());
        }
        catch (std::out_of_range &e)
        {
            PRINT_ERROR(e.what());
        }
    }
}

void ABot::listenGroupJoined(const std::string &message)
{
    _state.metadata["should_incant"] = "true";
}

void ABot::listenBroadcastResponse(const std::string &response)
{
    // Listeners Broadcast
    if (_allyMessage.content.find("group") != std::string::npos)
    {
        listenGroup(_allyMessage.content);
    }
    else if (_allyMessage.content.find("joined") != std::string::npos)
    {
        listenGroupJoined(_allyMessage.content);
    }
}
