/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Debug.cpp
*/
#include "../ABotProbabilistic.hpp"

void ABotProbabilistic::debugInitialisation()
{
    printColor("========== [Bot initiation] ==========\n", BLUE);
    printKeyValueColored("sockfd", std::to_string(_sockfd));
    printKeyValueColored("teamName", _teamName);
    printKeyValueColored("timeUnit", std::to_string(_timeUnit));
    printKeyValueColored("iteration", std::to_string(_iteration));
    printColor("========== [!Bot initiation] ==========\n\n", BLUE);
}

void ABotProbabilistic::debugProbabilities()
{
    printColor("========== [Bot Probabilities] ==========\n", BLUE);

    for (auto &probability : _probabilities)
    {
        printKeyValueColored(probability->name, std::to_string(probability->condition) + " " + std::to_string(probability->probability));
    }
    printColor("========== [!Bot Probabilities] ==========\n", BLUE);
}

void ABotProbabilistic::debugState()
{
    printColor("========== [Bot State] ==========\n", BLUE);
    printKeyValueColored("food", std::to_string(_state.ressources.food));
    printKeyValueColored("linemate", std::to_string(_state.ressources.linemate));
    printKeyValueColored("deraumere", std::to_string(_state.ressources.deraumere));
    printKeyValueColored("sibur", std::to_string(_state.ressources.sibur));
    printKeyValueColored("mendiane", std::to_string(_state.ressources.mendiane));
    printKeyValueColored("phiras", std::to_string(_state.ressources.phiras));
    printKeyValueColored("thystame", std::to_string(_state.ressources.thystame));
    printKeyValueColored("level", std::to_string(_state.level));
    printColor("========== [!Bot State] ==========\n", BLUE);
}
