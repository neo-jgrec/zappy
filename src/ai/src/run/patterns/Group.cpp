/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../ABotProbabilistic.hpp"
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
    if (_level == 2)
        _message._content = "group_3";
    else if (_level == 3)
        _message._content = "group_4";
    else if (_level == 4)
        _message._content = "group_5";
    else if (_level == 5)
        _message._content = "group_6";
    else if (_level == 6)
        _message._content = "group_7";
    else if (_level == 7)
        _message._content = "group_8";
    _message.vigenereEncrypt();
    _message.generateMessage();
    queue.push_back({[&]()
                     { doAction(BROADCAST, _message._content); }, "BROADCAST"});
}

void ABotProbabilistic::joinGroup()
{
    std::cout << _allyMessage._content << std::endl;
    std::string level = getElementAfter(_allyMessage._content, '_');
    std::cout << level << std::endl;
    if (getElementBefore(_allyMessage._content, '_') == "group"
        && std::stoi(level) == _level + 1
        && canLvlUp(_level + 1))
    {
        if (direction == "0") {
            printf("I'm in the group\n");
            return;
        }

        static const std::unordered_map<std::string, std::pair<std::string, std::function<void()>>> directionActions = {
            {"2", {"Forward", [&]() { doAction(FORWARD, ""); }}},
            {"1", {"Forward", [&]() { doAction(FORWARD, ""); }}},
            {"8", {"Forward", [&]() { doAction(FORWARD, ""); }}},
            {"5", {"Right", [&]() { doAction(RIGHT, ""); }}},
            {"6", {"Right", [&]() { doAction(RIGHT, ""); }}},
            {"7", {"Right", [&]() { doAction(RIGHT, ""); }}},
            {"3", {"Left", [&]() { doAction(LEFT, ""); }}},
            {"4", {"Left", [&]() { doAction(LEFT, ""); }}}
        };

        auto it = directionActions.find(direction);
        if (it != directionActions.end()) {
            const auto& action = it->second;
            printf("%s\n", action.first.c_str());
            queue.push_back({action.second, action.first});
        }
    }
}

bool ABotProbabilistic::canLvlUp(int lvl)
{
    if (lvl < 2 || lvl > 8)
        return false;

    const auto requirements = levelRequirements[lvl];

    bool hasRequiredResources =
        _state.ressources.linemate >= requirements[0] &&
        _state.ressources.deraumere >= requirements[1] &&
        _state.ressources.sibur >= requirements[2] &&
        _state.ressources.mendiane >= requirements[3] &&
        _state.ressources.phiras >= requirements[4] &&
        _state.ressources.thystame >= requirements[5];

    if (hasRequiredResources)
    {
        return true;
    }
    return false;
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