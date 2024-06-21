/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABot.hpp"

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
}
