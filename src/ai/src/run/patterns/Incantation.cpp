/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Incantation.cpp
*/

#include "../../bots/ABotPattern.hpp"

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
