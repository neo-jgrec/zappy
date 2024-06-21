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

// TODO: do bloc for lvl 1 and 2, etc...
void SimpleBot::updateStrategy()
{
    std::cout << "updateStrategy" << std::endl;
    if (_state.ressources.food < 5)
    {
        survive();
        _state.pattern = "survive";
    }
    else if (_state.state == SHOULD_GROUP)
    {
        joinGroup();
        _state.pattern = "joinGroup";
    }
    else if (_state.level == 1)
    {
        runToLinemate();
        _state.pattern = "runToLinemate";
    }
    else if (_state.level == 2 && _state.ressources.linemate != 1)
    {
        searchAndTakeRessource("linemate");
        _state.pattern = "searchAndTakeRessource: linemate";
    }
    else if (_state.level == 2 && _state.ressources.deraumere != 1)
    {
        searchAndTakeRessource("deraumere");
        _state.pattern = "searchAndTakeRessource: deraumere";
    }
    else if (_state.level == 2 && _state.ressources.sibur != 1)
    {
        searchAndTakeRessource("sibur");
        _state.pattern = "searchAndTakeRessource: sibur";
    }
    else if (_state.level == 2)
    {
        group();
        _state.pattern = "group";
    }
}
