/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

#include <iostream>
#include <string>
#include <sstream>

#include <iostream>
#include <string>
#include <sstream>

void ABot::listenGroup(const std::string &message)
{
    if (_state.metadata["should_group"] != "true") // TODO: rename it in process_group ?
    {
        try
        {
            size_t firstUnderscore = message.find('_');
            size_t secondUnderscore = message.find('_', firstUnderscore + 1);

            if (firstUnderscore == std::string::npos || secondUnderscore == std::string::npos)
            {
                throw std::invalid_argument("Invalid format: underscores not found");
            }

            std::string levelStr = message.substr(firstUnderscore + 1, secondUnderscore - firstUnderscore - 1);

            std::string currentIdGroup = message.substr(secondUnderscore + 1);

            unsigned int askLevel = std::stoi(levelStr);

            _state.metadata["id_group"] = currentIdGroup;

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
    size_t underscorePos = message.find('_');
    std::string idGroup = "0";
    std::cout << "here" << std::endl;
    std::cout << "message = " << message << std::endl;

    if (underscorePos != std::string::npos)
    {
        idGroup = message.substr(underscorePos + 1);
    }
    else
    {
        return;
    }
    std::cout << "idGroup = " << idGroup << std::endl;
    std::cout << "state id group = " << _state.metadata["id_group"] << std::endl;
    if (idGroup == _state.metadata["id_group"])
        _state.nbAlly++;
    if (_state.level == 2 || _state.level == 3)
    {
        if (_state.nbAlly >= 1)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
            // Landmark: 2. BROADCAST that every ones that follow this group should do otherting
            // should_group = false;
        }
    }
    else if (_state.level == 4 || _state.level == 5)
    {
        if (_state.nbAlly >= 3)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
            _state.nbAlly = 0;
        }
    }
    else if (_state.level == 6 || _state.level == 7)
    {
        if (_state.nbAlly >= 5)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
            _state.nbAlly = 0;
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
