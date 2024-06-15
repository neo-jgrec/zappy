/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Debug.cpp
*/
#include "../Bot.hpp"

void Bot::debugInitialisation()
{
    printColor("========== [Bot initiation] ==========\n", BLUE);
    printKeyValueColored("sockfd", std::to_string(_sockfd));
    printKeyValueColored("teamName", _teamName);
    printKeyValueColored("messageId", std::to_string(_messageId));
    printKeyValueColored("timeUnit", std::to_string(_timeUnit));
    printKeyValueColored("iteration", std::to_string(_iteration));
    printColor("========== [!Bot initiation] ==========\n\n", BLUE);
}

void Bot::debugProbabilities()
{
    for (auto &probability : probabilities)
    {
        printKeyValueColored(probability->name, std::to_string(probability->condition) + " " + std::to_string(probability->probability));
    }
}
