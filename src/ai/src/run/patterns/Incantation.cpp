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

// Landmark: 1. Fix this i guess. objStr is empty
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
