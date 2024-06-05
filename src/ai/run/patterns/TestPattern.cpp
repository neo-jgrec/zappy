/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../Bot.hpp"

void Bot::testPatern()
{
    doAction(LOOK, "");
    doAction(TAKE, "food");
    doAction(FORK, "");
    doAction(FORWARD, "");
    actionsCount = 4;
}

void Bot::testPatern2()
{
    doAction(FORWARD, "");
    doAction(TAKE, "food");
    doAction(RIGHT, "");
    doAction(FORWARD, "");
    doAction(TAKE, "food");
    actionsCount = 4;
}
