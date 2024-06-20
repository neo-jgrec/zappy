/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABot.cpp
*/

#include "ABot.hpp"

ABot::ABot() : _sockfd(-1), _teamName(""), _iteration(0)
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

void ABot::doAction(actions action, const std::string &parameter)
{
    ActionInfo actionInfo = getActionInfo(action);

    std::string finalAction = actionInfo.getName();
    if (parameter != "")
        finalAction += " " + parameter;
    printKeyValueColored("Bot does", finalAction);
    sendMessage(finalAction);
    _state.lastAction.action = action;
    _state.lastAction.parameter = parameter;
    _timeUnit -= actionInfo.getValue();
    if (_timeUnit % 126 == 0 && _state.ressources.food > 0)
    {
        _state.ressources.food -= 1;
    }

    // push into _state.actionsData if new action
    auto it = std::find_if(_state.actionsData.begin(), _state.actionsData.end(),
                           [&actionInfo](const ActionInfo &ad)
                           { return ad.getName() == actionInfo.getName(); });
    if (it == _state.actionsData.end()) // if action not found in actionsData
    {
        // Add new action to actionsData
        ActionInfo newActionInfo = actionInfo;
        newActionInfo.parameter = parameter;
        newActionInfo.count = 1;
        _state.actionsData.push_back(newActionInfo);

        // Print action and parameter
        std::cout << "New action added: " << finalAction << std::endl;
    }
    else
    {
        it->count += 1;
    }
}

// TODO: finis this.
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