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
    static int searchFood = 0;
    const unsigned int limitFood = 11;

    // survive has better success if better vision
    if (_state.ressources.food < limitFood)
    {
        if (_state.level == 2)
            searchFood = 20;
    }
    if (_state.level == 1)
    {
        runToLinemate();
        _state.pattern = "runToLinemate";
    }
    else if (searchFood > 0) // TODO: We can train an ia for this.
    {
        survive();
        _state.pattern = "survive";
        searchFood--;
    }
    else if (_state.state == SHOULD_GROUP)
    {
        joinGroup();
        _state.pattern = "joinGroup";
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
