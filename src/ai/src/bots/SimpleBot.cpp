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

    if (_state.level == 1)
    {
        handleLvl1();
        return;
    }
    if (handleSurvive())
        return;
    if (handleState())
        return;
    else if (_state.level == 2)
        handleLvl2();
    else if (_state.level == 3)
        handleLvl3();
}

bool SimpleBot::handleSurvive()
{
    static int searchFood = 0;
    const unsigned int limitFood = 11;

    if (_state.ressources.food < limitFood)
    {
        if (_state.level == 2)
            searchFood = 40;
    }
    if (searchFood > 0)
    {
        survive();
        _state.pattern = "survive";
        searchFood--;
        return true;
    }
    return false;
}

bool SimpleBot::handleState()
{
    if (_state.metadata["should_group"] == "true")
    {
        joinGroup();
        _state.pattern = "joinGroup";
        return true;
    }
    if (_state.metadata["should_incant"] == "true" && _state.level == 2)
    {
        incantationLvl2();
        _state.pattern = "incantationLvl2";
        return true;
    }

    return false;
}

void SimpleBot::handleLvl1()
{
    runToLinemate();
    _state.pattern = "runToLinemate";
}

void SimpleBot::handleLvl2()
{
    if (_state.ressources.linemate != 1)
    {
        searchAndTakeRessource("linemate");
        _state.pattern = "searchAndTakeRessource: linemate";
    }
    else if (_state.ressources.deraumere != 1)
    {
        searchAndTakeRessource("deraumere");
        _state.pattern = "searchAndTakeRessource: deraumere";
    }
    else if (_state.ressources.sibur != 1)
    {
        searchAndTakeRessource("sibur");
        _state.pattern = "searchAndTakeRessource: sibur";
    }
    group();
    _state.pattern = "group";
}

void SimpleBot::handleLvl3()
{
    std::cout << "ready for lvl 3" << std::endl;
}
