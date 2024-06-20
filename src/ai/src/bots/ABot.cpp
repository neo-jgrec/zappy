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
}

// TODO: finis this.
// void ABot::saveDataActions(const std::string &filename)
// {
//     std::ofstream out(filename, std::ios_base::app);

//     for (auto &action : _state.actionsData)
//     {
//         out << action.first << " " << action.second << std::endl;
//     }
//     out << "\n";
// }