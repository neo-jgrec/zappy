/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABot.cpp
*/

#include "ABotProbabilistic.hpp"

ABotProbabilistic::ABotProbabilistic() : _sockfd(-1), _teamName(""), _iteration(0)
{
    _orientation = NORTH;
    _state.ressources.food = 9;
}

ABotProbabilistic::~ABotProbabilistic()
{
}

void ABotProbabilistic::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

// if (_doNothing)
// {
//     _behaviors.erase(_behaviors.begin());
//     _behaviors.push_back(std::make_unique<Behavior>(0.4, [&]()
//                                                     { trapMessage(); }, "trap Message"));
//     _doNothing = false;
// }
void ABotProbabilistic::run(const std::string &response)
{
    std::string responseCopy = response;

    printColor("========== [Bot Run] ==========\n", BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    if (!responseCopy.empty() && responseCopy.back() == '\n')
    {
        responseCopy.pop_back();
    }
    printKeyValueColored("Bot listens", responseCopy);
    // if (responseCopy.find("message") != std::string::npos)
    //     _doNothing = true;
    listen(responseCopy);
    updateProbabilities();
    if (queue.empty())
        act(); // -> fait l'action la plus rentable
    if (!queue.empty())
    {
        queue.front().first();
        queue.erase(queue.begin());
    }
    _iteration++;
    printColor("========== [!Bot Run] ==========\n", BLUE);
    if (_iteration == 100)
    {
        debugState();
        exit(0);
    }
}

void ABotProbabilistic::listen(const std::string &response)
{
    if (_state.lastAction.action == LOOK)
        listenLookResponse(response);
    else if (_state.lastAction.action == TAKE)
        listenTakeResponse(response);
    else if (_state.lastAction.action == INCANTATION)
        listenIncantationResponse(response);
    if (response.find("message") != std::string::npos)
    {
        listenBroadcastResponse(response);
    }
}

void ABotProbabilistic::doAction(actions action, const std::string &parameter)
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
    if (_timeUnit % 126 == 0)
        _state.ressources.food -= 1;
}

void ABotProbabilistic::act()
{
    Behavior *bestBehavior = nullptr;

    double maxProbability = -1;

    if (!_behaviors.empty())
    {
        maxProbability = _behaviors[0]->probability;
        bestBehavior = _behaviors[0].get();
    }
    for (auto &behavior : _behaviors)
    {
        if (behavior->probability > maxProbability)
        {
            maxProbability = behavior->probability;
            bestBehavior = behavior.get();
        }
    }
    printColor("Behavior choosen: " + bestBehavior->name + "\n", BOLD);
    if (bestBehavior)
    {
        bestBehavior->act();
    }
}
