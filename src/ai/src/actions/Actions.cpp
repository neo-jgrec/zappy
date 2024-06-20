/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Actions.cpp
*/

#include "Actions.hpp"

// TODO: put it in constant
std::map<actions, ActionInfo> actionMap = {
    {DEFAULT, ActionInfo("Default", 0)},
    {FORWARD, ActionInfo("Forward", 7)},
    {RIGHT, ActionInfo("Right", 7)},
    {LEFT, ActionInfo("Left", 7)},
    {LOOK, ActionInfo("Look", 7)},
    {INVENTORY, ActionInfo("Inventory", 1)},
    {BROADCAST, ActionInfo("Broadcast", 7)},
    {CONNECT_NBR, ActionInfo("Connect_nbr", 0)},
    {FORK, ActionInfo("Fork", 42)},
    {EJECT, ActionInfo("Eject", 7)},
    {TAKE, ActionInfo("Take", 7)},
    {SET, ActionInfo("Set", 7)},
    {INCANTATION, ActionInfo("Incantation", 300)},
};

ActionInfo::ActionInfo(const std::string &name, int value) : name(name), value(value)
{
}

ActionInfo::~ActionInfo()
{
}

std::string ActionInfo::getName() const
{
    return name;
}

int ActionInfo::getValue() const
{
    return value;
}

ActionInfo getActionInfo(actions action)
{
    auto it = actionMap.find(action);

    if (it != actionMap.end())
        return it->second;
    else
        throw std::runtime_error("Action not found in actionMap"); // to verify: do a better throw
}
