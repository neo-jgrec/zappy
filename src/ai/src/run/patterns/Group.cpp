/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Survive.cpp
*/

#include "../../bots/ABotPattern.hpp"
#include "../../constant/Constants.hpp"
#include <functional>

void ABotPattern::group()
{
    if (_state.level == 2)
        _message.content = "group_3";
    else if (_state.level == 3)
        _message.content = "group_4";
    else if (_state.level == 4)
        _message.content = "group_5";
    else if (_state.level == 5)
        _message.content = "group_6";
    else if (_state.level == 6)
        _message.content = "group_7";
    else if (_state.level == 7)
        _message.content = "group_8";
    _message.format(_message.content);
    queue.push_back({[&]()
                     { doAction(BROADCAST, _message.content); }, "BROADCAST"});
}

void ABotPattern::joinGroup()
{
    if (_direction == "0")
    {
        _message.format("joined");
        queue.push_back({[&]()
                         { doAction(BROADCAST, _message.content); }, "BROADCAST"});
        _state.state = WAIT_FOR_SERVER_RESPONSE; // TODO: wait incant look response from server
        _state.metadata["wait_incant"] = "true";
        _state.metadata["should_group"] = "false";
        return;
    }
    std::cout << "group direction = " << _direction << std::endl;
    static const std::unordered_map<std::string, std::pair<std::string, std::function<void()>>> directionActions = {
        {"2", {"Forward", [&]()
               { doAction(FORWARD, ""); }}},
        {"1", {"Forward", [&]()
               { doAction(FORWARD, ""); }}},
        {"8", {"Forward", [&]()
               { doAction(FORWARD, ""); }}},
        {"5", {"Right", [&]()
               { doAction(RIGHT, ""); }}},
        {"6", {"Right", [&]()
               { doAction(RIGHT, ""); }}},
        {"7", {"Right", [&]()
               { doAction(RIGHT, ""); }}},
        {"3", {"Left", [&]()
               { doAction(LEFT, ""); }}},
        {"4", {"Left", [&]()
               { doAction(LEFT, ""); }}}};

    auto it = directionActions.find(_direction);
    if (it != directionActions.end())
    {
        const auto &action = it->second;
        printf("%s\n", action.first.c_str());
        queue.push_back({action.second, action.first});
    }
}

// TODO: remove it.
//  bool ABotProbabilistic::canLvlUp(int lvl)
//  {
//      if (lvl < 2 || lvl > 8)
//          return false;

//     const auto requirements = levelRequirements[lvl];

//     bool hasRequiredResources =
//         _state.ressources.linemate >= requirements[0] &&
//         _state.ressources.deraumere >= requirements[1] &&
//         _state.ressources.sibur >= requirements[2] &&
//         _state.ressources.mendiane >= requirements[3] &&
//         _state.ressources.phiras >= requirements[4] &&
//         _state.ressources.thystame >= requirements[5];

//     if (hasRequiredResources)
//     {
//         return true;
//     }
//     return false;
// }

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