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
    else if (_state.level == 4)
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
}

void ABot::listenBroadcastResponse(const std::string &response)
{
    std::string signature = getElementAfter(response, ':');

    if (signature != _signature)
    {
        _enemyMessage = _message.content;
        std::cout << "Enemy message: " << _enemyMessage.content << std::endl;
        return;
    }
    else
    {
        queue.clear();
        std::string temp = getElementBefore(response, ':');
        Message _allyMessage;
        _allyMessage.content = getElementAfter(temp, ',');
        _direction = getElementBefore(temp, ',');
        _allyMessage.direction = getElementAfter(_direction, ' ');
        _allyMessage.vigenereDecrypt();
        printKeyValueColored("Message", _allyMessage.content);
        printKeyValueColored("Direction", _direction);
        _alliesMessage.push_back(_allyMessage);
    }
    for (auto &_allyMessage : _alliesMessage) {
        if (_allyMessage.content.find("group") != std::string::npos)
        {
            listenGroup(_allyMessage.content);
        }
        else if (_allyMessage.content.find("joined") != std::string::npos && _state.metadata["ask_for_group"] == "true")
        {
            listenGroupJoined(_allyMessage.content);
        }
    }
    // Listeners Broadcast
}
