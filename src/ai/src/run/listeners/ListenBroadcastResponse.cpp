/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

void ABot::listenGroup(const std::string &response)
{
    try
    {
        if (!response.empty())
        {
            std::string lastChar(1, response.back());
            int askLevel = std::stoi(lastChar);
            std::cout << "response = " << response << std::endl;

            if (_state.level == askLevel)
            {
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
            listenGroup(response);
        }
    }
}
