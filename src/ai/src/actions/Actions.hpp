/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Actions.hpp
*/

#ifndef ACTIONS_HPP_
#define ACTIONS_HPP_

#include <iostream>
#include <map>

enum actions
{
    DEFAULT,
    FORWARD,
    RIGHT,
    LEFT,
    LOOK,
    INVENTORY,
    BROADCAST,
    CONNECT_NBR,
    FORK,
    EJECT,
    TAKE,
    SET,
    INCANTATION,
};

class ActionInfo
{
public:
    ActionInfo(const std::string &name, int value);
    ~ActionInfo();

    std::string getName() const;
    int getValue() const;
    std::string parameter;

private:
    std::string name;
    int value;
};

extern std::map<actions, ActionInfo> actionMap;

ActionInfo getActionInfo(actions action);

#endif // ACTIONS_HPP_
