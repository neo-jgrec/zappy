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
    // TODO: add it in ABot or somewhere (metadata ?)?
    static unsigned int playersPresent = 0;

    if (_state.level == 2 || _state.level == 3)
    {
        _state.metadata["should_incant"] = "true";
        _state.metadata["ask_for_group"] = "false";
    }
    else if (_state.level == 4 || _state.level == 5)
    {
        std::cout << "playersPresent: " << playersPresent << std::endl;
        playersPresent++;
        if (playersPresent == 3)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
            playersPresent = 0;
        }
    }
    else if (_state.level == 6 || _state.level == 7)
    {
        std::cout << "playersPresent: " << playersPresent << std::endl;
        playersPresent++;
        if (playersPresent == 5)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
            playersPresent = 0;
        }
    }
}

// TODO: find somehow how to rename it in listenGroupDone
void ABot::listenMeetingDone(const std::string &message)
{
    _state.metadata["should_group"] = "false";
}

void ABot::listenBroadcastResponse(const std::string &response)
{
    // Listeners Broadcast
    if (_allyMessage.content.find("group") != std::string::npos)
    {
        listenGroup(_allyMessage.content);
    }
    else if (_allyMessage.content.find("joined") != std::string::npos && _state.metadata["ask_for_group"] == "true")
    {
        listenGroupJoined(_allyMessage.content);
    }
    else if (_allyMessage.content.find("meeting") != std::string::npos)
    {
        listenMeetingDone(_allyMessage.content);
    }
}
