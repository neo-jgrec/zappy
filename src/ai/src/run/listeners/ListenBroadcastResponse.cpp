/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABotProbabilistic.hpp"

void ABotProbabilistic::listenBroadcastResponse(const std::string &response)
{
    std::string signature = getElementAfter(response, ':');
    Message tempMessage;
    if (signature != _signature)
    {
        _enemyMessage = _message._content;
        std::cout << "Enemy message: " << _enemyMessage._content << std::endl;
        return;
    }
    else
    {
        std::string temp = getElementBefore(response, ':');
        tempMessage._content = getElementAfter(temp, ',');
        direction = getElementBefore(temp, ',');
        direction = getElementAfter(direction, ' ');
        tempMessage.vigenereDecrypt();
        printKeyValueColored("Message", tempMessage._content);
        printKeyValueColored("Direction", direction);
    }
}
