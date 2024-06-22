/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Incantation.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::incantationLvl1()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}

void ABotPattern::incantationLvl2()
{
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    _state.ressources.linemate--;
    queue.push_back({[&]()
                     { doAction(SET, "deraumere"); }, "SET"});
    _state.ressources.deraumere--;
    queue.push_back({[&]()
                     { doAction(SET, "sibur"); }, "SET"});
    _state.ressources.sibur--;
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
    _state.metadata["should_incant"] = "false";
}

// TODO: Fix this i guess. objStr is empty
void ABotPattern::incantation(std::vector<std::string> objs)
{
    for (auto &obj : objs)
    {
        std::string objStr = obj;

        queue.push_back({[&]()
                         { doAction(SET, objStr); }, "SET"});
        if (obj == "linemate")
            _state.ressources.linemate--;
    }
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}
