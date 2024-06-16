/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../../Bot.hpp"
#include <functional>

void Bot::survive()
{
    searchAndTakeRessource("food");
    _message.generateMessage("group");
    _message.vigenereEncrypt();
    queue.push_back({[&]() { doAction(BROADCAST, _message._content); }, "BROADCAST"});
}