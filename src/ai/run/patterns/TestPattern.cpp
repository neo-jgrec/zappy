/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../Bot.hpp"
#include <functional>

void Bot::testPatern()
{
    queue.push_back({[&]() { doAction(LOOK, ""); }, "LOOK"});
    queue.push_back({[&]() { doAction(FORWARD, ""); }, "FORWARD"});
    queue.push_back({[&]() { doAction(TAKE, "food"); }, "TAKE"});
    queue.push_back({[&]() { doAction(RIGHT, ""); }, "RIGHT"});
}

void Bot::sentinelle()
{
}