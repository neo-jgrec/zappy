/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../bots/ABotProbabilistic.hpp"
#include <functional>

void ABotProbabilistic::turnLeft(std::pair<int, int> &pos)
{
    _orientation = static_cast<Orientation>((_orientation + 3) % 4);
}

void ABotProbabilistic::turnRight(std::pair<int, int> &pos)
{
    _orientation = static_cast<Orientation>((_orientation + 1) % 4);
}

void ABotProbabilistic::moveForward(std::pair<int, int> &pos)
{
    switch (_orientation)
    {
    case NORTH:
        pos.second++;
        break;
    case EAST:
        pos.first++;
        break;
    case SOUTH:
        pos.second--;
        break;
    case WEST:
        pos.first--;
        break;
    }
    queue.push_back({[&]()
                     { doAction(FORWARD, ""); }, "FORWARD"});
}

void ABotProbabilistic::turnToDirection(std::pair<int, int> &pos, Orientation targetDir)
{
    int leftTurns = (_orientation - targetDir + 4) % 4;
    int rightTurns = (targetDir - _orientation + 4) % 4;

    if (leftTurns <= rightTurns)
    {
        for (int i = 0; i < leftTurns; ++i)
        {
            turnLeft(pos);
            queue.push_back({[&]()
                             { doAction(LEFT, ""); }, "LEFT"});
        }
    }
    else
    {
        for (int i = 0; i < rightTurns; ++i)
        {
            turnRight(pos);
            queue.push_back({[&]()
                             { doAction(RIGHT, ""); }, "RIGHT"});
        }
    }
}

void ABotProbabilistic::findPath(std::pair<int, int> start, const std::pair<int, int> &end)
{
    static const std::vector<std::pair<int, Orientation>> directions = {
        {1, EAST}, {-1, WEST}, {1, NORTH}, {-1, SOUTH}};

    while (start != end)
    {
        for (const auto &[delta, dir] : directions)
        {
            if ((dir == EAST || dir == WEST) && start.first != end.first && (dir == EAST ? start.first < end.first : start.first > end.first))
            {
                turnToDirection(start, dir);
                moveForward(start);
                break;
            }
            else if ((dir == NORTH || dir == SOUTH) && start.second != end.second && (dir == NORTH ? start.second < end.second : start.second > end.second))
            {
                turnToDirection(start, dir);
                moveForward(start);
                break;
            }
        }
    }
}

void ABotProbabilistic::group()
{
    findPath({0, 0}, {-10, -10});
}

/*void Bot::findPath(std::pair<int, int> start, const std::pair<int, int> &end)
{
    while (start.first != end.first || start.second != end.second) {
        if (start.first < end.first) {
            turnToDirection(start, EAST);
            moveForward(start);
        } else if (start.first > end.first) {
            turnToDirection(start, WEST);
            moveForward(start);
        } else if (start.second < end.second) {
            turnToDirection(start, NORTH);
            moveForward(start);
        } else if (start.second > end.second) {
            turnToDirection(start, SOUTH);
            moveForward(start);
        }
    }
}*/