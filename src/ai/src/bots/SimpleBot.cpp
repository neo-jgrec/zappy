/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** SimpleBot.cpp
*/

#include "SimpleBot.hpp"

void SimpleBot::initChild()
{

    std::cout << "🤖 SimpleBot initialized" << std::endl;
}

void SimpleBot::updateStrategy()
{
    std::cout << "🤖 SimpleBot updateStrategy" << std::endl;
    queue.push_back(std::make_pair([&]()
                                   { doAction(FORWARD, ""); }, "FORWARD"));
    if (_state.ressources.food < 5)
        survive();
    else if (_state.level == 1 && _state.ressources.linemate != 1)
        searchAndTakeRessource("linemate");
    else if (_state.ressources.linemate == 1 && _state.level == 1)
        incantationLvl1();
}
