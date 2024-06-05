/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../Bot.hpp"

void Bot::testPatern()
{
    queue.push_back([&]()
                    { doAction(LOOK, ""); });
    queue.push_back([&]()
                    { doAction(FORWARD, ""); });
    queue.push_back([&]()
                    { doAction(TAKE, "food"); });
    queue.push_back([&]()
                    { doAction(RIGHT, ""); });
}

void Bot::testPatern2()
{
    queue.push_back([&]()
                    { doAction(FORWARD, ""); });
    queue.push_back([&]()
                    { doAction(TAKE, "food"); });
}
