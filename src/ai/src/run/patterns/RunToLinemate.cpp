/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** RunToLinemate.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::runToLinemate()
{
    if (_state.metadata["should_update_env"] == "true")
    {
        if (_iteration > 50 && _iteration < 55)
            queue.push_back({[&]()
                             { doAction(LEFT, ""); }, "LEFT"});
        if (_iteration > 100 && _iteration < 105)
            queue.push_back({[&]()
                             { doAction(RIGHT, ""); }, "RIGHT"});
        queue.push_back({[&]()
                         { doAction(LOOK, ""); }, "LOOK"});
        return;
    }
    else
    {
        std::unordered_map<std::string, std::function<void()>> actions = {
            {"FORWARD", [&]()
             { doAction(FORWARD, ""); }},
            {"LEFT", [&]()
             { doAction(LEFT, ""); }},
            {"RIGHT", [&]()
             { doAction(RIGHT, ""); }},
        };
        std::unique_ptr<Tile> tile = _state.environment.getTileByRessource("linemate");
        if (tile != nullptr)
        {
            std::pair<int, int> coord = {tile->x, tile->y};
            if (movementMap.find(coord) != movementMap.end())
            {
                for (const auto &move : movementMap[coord])
                {
                    queue.push_back({actions[move], move});
                }
            }
            queue.push_back({[&]()
                             { doAction(INCANTATION, ""); }, "INCANTATION"});
        }
        if (tile == nullptr)
        {
            queue.push_back({[&]()
                             { doAction(FORWARD, ""); }, "FORWARD"});
        }
    }
}