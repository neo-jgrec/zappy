/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../Bot.hpp"

void Bot::listenBroadcastResponse(const std::string &response)
{
    std::string message = getElementAfter(response, ',');
    _message._content = message;
    std::string signature = getElementAfter(_message._content, ':');
    if (signature != _signature) {
        _enemyMessage = _message._content;
        std::cout << "Enemy message: " << _enemyMessage._content << std::endl;
        return;
    } else {
        _message._content = getElementBefore(_message._content, ':');
        _message.vigenereDecrypt();
        printKeyValueColored("Message", _message._content);
    }
}