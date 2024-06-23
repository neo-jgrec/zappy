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
    std::cout << "🧒🔄 SimpleBot updateStrategy" << std::endl;
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
    else if (_state.level == 4)
        handleLvl4();
    else
        PRINT_ALERT("🧒❌ SimpleBot: level not handled\n");
}

bool SimpleBot::handleSurvive()
{
    static int searchFood = 0;
    const unsigned int limitFood = 20;

    if (_iteration % 40 == 0)
    {
        _state.state = STANDARD;
        queue.push_back({[&]()
                         { doAction(INVENTORY, ""); }, "INVENTORY"});
        return true;
    }

    if (_state.ressources.food < limitFood)
    {
        if (_state.level == 2)
            searchFood = 150;
    }
    if (searchFood > 0)
    {
        if (searchFood == 1)
            queue.push_back({[&]()
                             { doAction(INVENTORY, ""); }, "INVENTORY"});
        else
            survive();
        _state.state = STANDARD;
        _state.pattern = "survive";
        searchFood--;
        return true;
    }
    return false;
}

bool SimpleBot::handleState()
{
    if (_state.metadata["should_incant"] == "true")
    {
        _message.format("meeting" + std::to_string(_state.level + 1) + "done");
        queue.push_back({[&]()
                         { doAction(BROADCAST, _message.content); }, "BROADCAST"});
    }
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
    if (_state.metadata["should_incant"] == "true" && _state.level == 3)
    {
        incantationLvl3();
        _state.pattern = "incantationLvl3";
        return true;
    }
    if (_state.metadata["should_incant"] == "true" && _state.level == 4)
    {
        incantationLvl4();
        _state.pattern = "incantationLvl4";
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
    else
    {
        group();
        _state.pattern = "group";
    }
}

void SimpleBot::handleLvl3()
{
    if (_state.ressources.linemate != 2)
    {
        searchAndTakeRessource("linemate");
        _state.pattern = "searchAndTakeRessource: linemate";
    }
    else if (_state.ressources.sibur != 1)
    {
        searchAndTakeRessource("sibur");
        _state.pattern = "searchAndTakeRessource: sibur";
    }
    else if (_state.ressources.phiras != 2)
    {
        searchAndTakeRessource("phiras");
        _state.pattern = "searchAndTakeRessource: phiras";
    }
    else
    {
        group();
        _state.pattern = "group";
    }
}

void SimpleBot::handleLvl4()
{
    PRINT_ALERT("handleLvl4\n");
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
    else if (_state.ressources.sibur != 2)
    {
        searchAndTakeRessource("sibur");
        _state.pattern = "searchAndTakeRessource: sibur";
    }
    else if (_state.ressources.phiras != 1)
    {
        searchAndTakeRessource("phiras");
        _state.pattern = "searchAndTakeRessource: phiras";
    }
    else
    {
        group();
        _state.pattern = "group";
    }
}

// TODO: fix: don't use food on time unit because sometimes bot only wait so his fod don't decrease.
//  TODO: sometimes it group but don't survive
//  TODO (MAYBE): handle when both can group: rule bot id < bot 2 id group, the other join group
