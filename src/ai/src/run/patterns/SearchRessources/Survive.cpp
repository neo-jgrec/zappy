/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../../ABotProbabilistic.hpp"
#include <functional>

void ABotProbabilistic::survive()
{
    searchAndTakeRessource("food");
    _message.generateMessage("group");
    _message.vigenereEncrypt();
    queue.push_back({[&]()
                     { doAction(BROADCAST, _message._content); }, "BROADCAST"});
}
