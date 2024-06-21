/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Actions.cpp
*/

#include "Actions.hpp"

// TODO: how to put it in constant without conflict ?
std::map<Action, ActionInfo> actionMap = {
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

ActionInfo::ActionInfo(const std::string &name, unsigned int timeUnitCost) : _name(name), _timeUnitCost(timeUnitCost)
{
}

ActionInfo::~ActionInfo()
{
}

std::string ActionInfo::getName() const
{
    return _name;
}

unsigned int ActionInfo::getTimeUnitCost() const
{
    return _timeUnitCost;
}

ActionInfo getActionInfo(Action action)
{
    auto it = actionMap.find(action);

    if (it != actionMap.end())
    {
        ActionInfo actionInfo = it->second;

        actionInfo.action = action;
        return actionInfo;
    }
    else
        throw ActionInfoException("Action not found in actionMap");
}
