/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenGroup(const std::string &message)
{
    if (_state.state != SHOULD_GROUP)
    {
        try
        {
            if (!message.empty())
            {
                std::string lastChar(1, message.back());
                unsigned int askLevel = std::stoi(lastChar);

                if (_state.level + 1 == askLevel)
                {
                    queue.clear();
                    _state.state = SHOULD_GROUP;
                }
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
    std::cout << "GROUP JOIN" << std::endl;
    exit(0);
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
        std::string temp = getElementBefore(response, ':');
        _allyMessage.content = getElementAfter(temp, ',');
        _direction = getElementBefore(temp, ',');
        _direction = getElementAfter(_direction, ' ');
        _allyMessage.vigenereDecrypt();
        printKeyValueColored("Message", _allyMessage.content);
        printKeyValueColored("Direction", _direction);
    }
    // Listeners Broadcast
    if (_allyMessage.content.find("group") != std::string::npos)
    {
        listenGroup(_allyMessage.content);
    }
    else if (_allyMessage.content.find("group_joined") != std::string::npos)
    {
        listenGroupJoined(_allyMessage.content);
    }
}
