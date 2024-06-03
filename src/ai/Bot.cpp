/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _messageId(0), _timeUnit(126)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    printColor("===== [Bot initiation] =====", GREEN);
    printColor("sockfd: " + std::to_string(_sockfd), YELLOW);
    printColor("teamName: " + _teamName, YELLOW);
    printColor("messageId: " + std::to_string(_messageId), YELLOW);
    printColor("timeUnit: " + std::to_string(_timeUnit), YELLOW);
    std::cout << std::endl;

    sendMessage(teamName);
    state.ressources.food = 9;
    behaviors.push_back(std::make_unique<Behavior>(0, [&]()
                                                   { doAction(LOOK, ""); }, "look"));
    behaviors.push_back(std::make_unique<Behavior>(0, [&]()
                                                   { doAction(TAKE, "food"); }, "take"));
    behaviors.push_back(std::make_unique<Behavior>(0, [&]()
                                                   { doAction(FORK, ""); }, "fork"));
    for (auto &behavior : behaviors)
    {
        behavior->probability = rand() % 100;
    }
    printColor("===== [!Bot initiation] =====", GREEN);
}

Bot::~Bot()
{
}

void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Bot::run(std::string response)
{
    printColor("Bot listens: " + response, GREEN);

    listen(response); // -> change le state
    act();            // -> fait l'action la plus rentable
}

void Bot::act()
{
    Behavior *bestBehavior = nullptr;
    int maxProbability = -1;

    for (auto &behavior : behaviors)
    {
        std::cout << "name: " << behavior->name << " probability: " << behavior->probability << std::endl;
        if (behavior->probability > maxProbability)
        {
            maxProbability = behavior->probability;
            bestBehavior = behavior.get();
        }
    }
    std::cout << "bestBehavior: " << bestBehavior->name << std::endl;

    if (bestBehavior)
    {
        bestBehavior->act();
    }
}

void Bot::listen(std::string response)
{
    if (state.lastAction.action == LOOK)
    {
        listenLookResponse(response);
    }
    else if (state.lastAction.action == FORK)
    {
        listenForkResponse(response);
    }
}

void Bot::takeFirstDecision(std::string response)
{
    int slot;
    int x; // to verify: we want to store that in bot ? behavior different if map is larger ?
    int y;

    std::string modifiedInput = response;
    std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
    std::istringstream iss(modifiedInput);
    iss >> slot >> x >> y;

    if (slot == 0)
        doAction(FORK, "");
    else
        doAction(LOOK, "");
}

void Bot::doAction(actions action, const std::string &parameter)
{
    ActionInfo actionInfo = getActionInfo(action);

    std::string finalAction = actionInfo.getName();

    if (parameter != "")
        finalAction += " " + parameter;
    printColor("Bot does: " + finalAction, YELLOW);
    sendMessage(finalAction);
    state.lastAction.action = action;
    state.lastAction.parameter = parameter;
    _timeUnit -= actionInfo.getValue();
    if (_timeUnit % 126 == 0)
        state.ressources.food -= 1;
}

/* [ML] */
/* [AddObservation]
What bot will change
last behavior.probability

and

Botstate

will modify the last behavior.probability
*/

/* [Rewards]
An action occured
food * 0.1;
linemate * 0.2;
deraumere * 0.3;
reached a lvl = nb_lvl * 0.3

die = -1
get ko response ? (not sure)
*/