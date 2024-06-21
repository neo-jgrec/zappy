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

enum Action
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

class ActionInfoException : public std::exception
{

public:
    ActionInfoException(const std::string &msg) : _msg(msg) {}
    const char *what() const noexcept override { return _msg.c_str(); }

private:
    std::string _msg;
};

class ActionInfo
{
public:
    ActionInfo(const std::string &name, unsigned int timeUnitCost);
    ~ActionInfo();

    Action action = DEFAULT;
    std::string getName() const;
    unsigned int getTimeUnitCost() const;

    std::string parameter;
    unsigned int count = 0;

private:
    std::string _name;
    unsigned int _timeUnitCost;
};

extern std::map<Action, ActionInfo> actionMap;

ActionInfo getActionInfo(Action action);

#endif // ACTIONS_HPP_
