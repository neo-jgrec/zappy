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
    _message.vigenereDecrypt();
    std::string signature = getElementAfter(_message._content, ':');
    printKeyValueColored("Message", _message._content);
}