/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../../bots/ABot.hpp"

#include <iostream>
#include <string>
#include <sstream>

void ABot::listenBroadcastResponse(std::vector<Message> &_alliesMessage_)
{
    // Listeners Broadcast
    for (auto &_allyMessage : _alliesMessage_) {
        if (_allyMessage.content.find("group") != std::string::npos)
        {
            listenGroupBroadcast(_allyMessage.content);
        }
        else if (_allyMessage.content.find("joined") != std::string::npos && _state.metadata["ask_for_group"] == "true")
        {
            listenGroupJoinedBroadcast(_allyMessage.content);
        }
        else if (_allyMessage.content.find("meeting") != std::string::npos)
        {
            listenMeetingDoneBroadcast(_allyMessage.content);
        }
        else if (_allyMessage.content.find("warns"))
            listenWarnsBroadcast(_allyMessage.content);
    }
}
