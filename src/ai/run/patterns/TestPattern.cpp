/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** TestPattern.cpp
*/

#include "../../Bot.hpp"
#include <functional>

void Bot::testPatern()
{
    queue.push_back({[&]() { doAction(LOOK, ""); }, "LOOK"});
    queue.push_back({[&]() { doAction(FORWARD, ""); }, "FORWARD"});
    queue.push_back({[&]() { doAction(TAKE, "food"); }, "TAKE"});
    queue.push_back({[&]() { doAction(RIGHT, ""); }, "RIGHT"});
}

void Bot::survive()
{
    if (state.environment.tiles.empty())
    {
        queue.push_back({[&]() { doAction(LOOK, ""); }, "LOOK"});
    }

    std::unordered_map<std::string, std::function<void()>> actions = {
        { "FORWARD", [&]() { doAction(FORWARD, ""); } },
        { "LEFT",    [&]() { doAction(LEFT, ""); } },
        { "RIGHT",   [&]() { doAction(RIGHT, ""); } },
        { "TAKE",    [&]() { doAction(TAKE, "food"); } }
    };

    bool foodFound = false;

    for (const auto& tile : state.environment.tiles)
    {
        std::cout << "Tile: " << tile.x << " " << tile.y << std::endl;
        std::cout << "food: " << tile.ressources.food << std::endl;
        std::cout << "distance: " << tile.distance << std::endl;
        
        if (tile.ressources.food > 0)
        {
            foodFound = true;
            std::pair<int, int> coord = {tile.x, tile.y};
            if (movementMap.find(coord) != movementMap.end())
            {
                for (const auto& move : movementMap[coord])
                {
                    queue.push_back({ actions[move], move });
                }
            }
            queue.push_back({ actions["TAKE"], "TAKE" });
            break;
        }
    }

    if (!foodFound)
        queue.push_back({[&]() { doAction(FORWARD, ""); }, "FORWARD"});

    queue.push_back({[&]() { doAction(LOOK, ""); }, "LOOK"});
}

void Bot::group()
{
    findPath({0, 0}, {-10, 5});
}