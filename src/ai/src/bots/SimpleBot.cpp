/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** SimpleBot.cpp
*/

#include "SimpleBot.hpp"

void SimpleBot::initChild()
{
    std::cout << "🧒✅ SimpleBot initialized" << std::endl;
}

void SimpleBot::updateStrategy()
{
    if (_state.ressources.food < 5)
        survive();
    else if (_state.level == 1 && _state.ressources.linemate != 1)
        searchAndTakeRessource("linemate");
    else if (_state.ressources.linemate == 1 && _state.level == 1)
        incantationLvl1();
    else if (_state.level == 2 && _state.ressources.linemate != 1)
        searchAndTakeRessource("linemate");
}
