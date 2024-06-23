/*
** EPITECH PROJECT, 2024
** zappy/ai/run/listeners/broadcast
** File description:
** ListenGroupBroadcast.cpp
*/

#include "../../../bots/ABot.hpp"

#include <iostream>
#include <string>
#include <sstream>

void ABot::listenGroupBroadcast(const std::string &message)
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

void ABot::listenGroupJoinedBroadcast(const std::string &message)
{
    size_t underscorePos = message.find('_');
    std::string idGroup = "0";

    if (underscorePos != std::string::npos)
    {
        idGroup = message.substr(underscorePos + 1);
    }
    else
    {
        return;
    }
    if (idGroup == _state.metadata["id_group"])
        _state.nbAlly++;
    if (_state.level == 2 || _state.level == 3)
    {
        if (_state.nbAlly >= 1)
        {
            _state.metadata["should_incant"] = "true";
            _state.metadata["ask_for_group"] = "false";
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

void ABot::listenMeetingDoneBroadcast(const std::string &message)
{
    const std::string prefix = "meeting_";
    const std::string suffix = "_done";
    std::string messageCopy = message;

    if (messageCopy.find(prefix) == 0 && messageCopy.rfind(suffix) == (messageCopy.length() - suffix.length()))
    {
        std::string idGroup = messageCopy.substr(prefix.length(), messageCopy.length() - prefix.length() - suffix.length());
        if (idGroup == _state.metadata["id_group"])
        {
            _state.metadata["should_group"] = "false";
            _state.state = STANDARD;
        }
    }
}

void ABot::listenWarnsBroadcast(const std::string &message)
{
    const std::string prefix = "warns_will_incant_";

    if (message.rfind(prefix, 0) == 0)
    {
        std::string idGroup = message.substr(prefix.length());
        if (idGroup == _state.metadata["id_group"])
        {
            _state.metadata["should_group"] = "false";
            _state.state = STANDARD;
        }
    }
}
