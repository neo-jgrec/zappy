/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../bots/ABotPattern.hpp"
#include <functional>

void ABotPattern::testPatern()
{
    queue.push_back({[&]()
                     { doAction(LOOK, ""); }, "LOOK"});
    queue.push_back({[&]()
                     { doAction(FORWARD, ""); }, "FORWARD"});
    queue.push_back({[&]()
                     { doAction(TAKE, "food"); }, "TAKE"});
    queue.push_back({[&]()
                     { doAction(RIGHT, ""); }, "RIGHT"});
}

void ABotPattern::trapMessage()
{
    std::string trapMessage = replaceNumbersInString(_enemyMessage.content, 1200);
    if (trapMessage.empty())
        trapMessage = _enemyMessage.content;
    std::cout << "trapMessage: " << trapMessage << std::endl;
    queue.push_back({[&]()
                     { doAction(BROADCAST, trapMessage); }, "BROADCAST"});
}