/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::listenBroadcastResponse(const std::string &response)
{
    std::string signature = getElementAfter(response, ':');

    if (signature != _signature)
    {
        _enemyMessage = _message._content;
        std::cout << "Enemy message: " << _enemyMessage._content << std::endl;
        return;
    }
    else
    {
        std::string temp = getElementBefore(response, ':');
        _allyMessage._content = getElementAfter(temp, ',');
        direction = getElementBefore(temp, ',');
        direction = getElementAfter(direction, ' ');
        _allyMessage.vigenereDecrypt();
        printKeyValueColored("Message", _allyMessage._content);
        printKeyValueColored("Direction", direction);
    }
}
