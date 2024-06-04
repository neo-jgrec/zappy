/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../Bot.hpp"

void Bot::testPatern()
{
    doAction(LOOK, "", "look");
    doAction(TAKE, "food", "take_food");
    doAction(FORK, "", "fork");
    doAction(FORWARD, "", "forward");
    actionsCount = 4;
}
