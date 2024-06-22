/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../../bots/ABotPattern.hpp"
#include "../../../constant/Constants.hpp"
#include <functional>

void ABotPattern::searchAndTakeRessource(const std::string &ressource)
{

    if (_state.metadata["should_update_env"] == "true")
    {
        queue.push_back({[&]()
                         { doAction(LOOK, ""); }, "LOOK"});
        return;
    }
    else
    {
        // TODO: find a way to add it to constant, this code is copy paste in RunToLinemate.cpp
        std::unordered_map<std::string, std::function<void()>> actions = {
            {"FORWARD", [&]()
             { doAction(FORWARD, ""); }},
            {"LEFT", [&]()
             { doAction(LEFT, ""); }},
            {"RIGHT", [&]()
             { doAction(RIGHT, ""); }},
            {"TAKE", [=]()
             { doAction(TAKE, ressource); }}};

        std::unique_ptr<Tile> tile = _state.environment.getTileByRessource(ressource);
        if (tile != nullptr)
        {
            std::pair<int, int> coord = {tile->x, tile->y};
            // std::cout << "tile = " << tile->x << " " << tile->y << std::endl;
            if (movementMap.find(coord) != movementMap.end())
            {
                for (const auto &move : movementMap[coord])
                {
                    queue.push_back({actions[move], move});
                    // std::cout << "movement to go the tile = " << move << std::endl;
                }
            }
            queue.push_back({actions["TAKE"], "TAKE"});
        }

        if (tile == nullptr)
        {
            queue.push_back({[&]()
                             { doAction(FORWARD, ""); }, "FORWARD"});
        }
    }
}