/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABot.cpp
*/

#include "ABot.hpp"

ABot::ABot()
{
    _state.ressources.food = 9;
}

ABot::~ABot()
{
}

void ABot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

// TODO: decrypt parameter in a tmp to debug it easily.
void ABot::doAction(Action action, const std::string &parameter)
{
    static int timeUnit = 126;

    try
    {
        ActionInfo actionInfo = getActionInfo(action);
        std::string actionToServer = actionInfo.getName();

        if (parameter != "")
            actionToServer += " " + parameter;
        printKeyValueColored("🤖🤜 Bot does", actionToServer);
        sendMessage(actionToServer);

        _state.lastAction.action = action;
        _state.lastAction.parameter = parameter;
        timeUnit -= actionInfo.getTimeUnitCost();

        if (timeUnit < 126 && _state.ressources.food > 0)
        {
            _state.ressources.food -= 1;
            timeUnit += 126;
        }
        saveMetrics(actionInfo);
    }
    catch (const ActionInfoException &e)
    {
        PRINT_ERROR(e.what());
    }
    // Bots moved or took a ressource, his environment changed
    if (action == FORWARD || action == RIGHT || action == LEFT || action == TAKE || action == INCANTATION)
        _state.metadata["should_update_env"] = "true";
    if (action == LOOK)
        _state.metadata["should_update_env"] = "false";
}

void ABot::saveMetrics(ActionInfo actionInfo)
{
    auto it = std::find_if(_state.actionsData.begin(), _state.actionsData.end(),
                           [&actionInfo](const ActionInfo &ad)
                           { return ad.getName() == actionInfo.getName(); });
    if (it == _state.actionsData.end())
    {
        ActionInfo newActionInfo = actionInfo;

        newActionInfo.parameter = actionInfo.parameter;
        newActionInfo.count = 1;
        _state.actionsData.push_back(newActionInfo);
    }
    else
    {
        it->count += 1;
    }
}

void ABot::saveDataActions(const std::string &filename)
{
    std::ofstream out(filename, std::ios_base::app);

    out << "Iteration:" << _iteration << std::endl;
    for (auto &action : _state.actionsData)
    {
        out << action.getName();
        if (!action.parameter.empty())
            out << " " << action.parameter;
        out << ":" + std::to_string(action.count) << std::endl;
    }
    out << "\n";
}