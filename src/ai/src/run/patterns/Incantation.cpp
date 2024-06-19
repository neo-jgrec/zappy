/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Incantation.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::incantation(std::vector<std::string> objs)
{
    // Landmark: 1. Fix this.
    // for (auto &obj : objs)
    // {
    //     std::string objStr = obj;

    //     queue.push_back({[&]()
    //                      { doAction(SET, objStr); }, "SET"});
    //     if (obj == "linemate")
    //         _state.ressources.linemate--; // TODO: do a clean way to remove ressources
    // }
    queue.push_back({[&]()
                     { doAction(SET, "linemate"); }, "SET"});
    // Landmark: 2. Fix queue and this. When it listen Incant it is in two steps.
    // Dont do action after first listen of incantation
    queue.push_back({[&]()
                     { doAction(INCANTATION, ""); }, "INCANTATION"});
}
