/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _messageId(0), _timeUnit(126), _shouldListen(false)
{
    printColor("===== [Bot initiation] =====", GREEN);
    printColor("sockfd: " + std::to_string(_sockfd), YELLOW);
    printColor("teamName: " + _teamName, YELLOW);
    printColor("messageId: " + std::to_string(_messageId), YELLOW);
    printColor("timeUnit: " + std::to_string(_timeUnit), YELLOW);
    printColor("===== [!Bot initiation] =====", GREEN);
    std::cout << std::endl;

    sendMessage(teamName);
    state.ressources.food = 9;
    // ACTIONS WITH THEIR PROBABILITIES
    // LOOK IS ONE BECAUSE IT IS THE FIRST ACTION WE WANT TO DO AFTER FIRST DECISION
    Behavior look = Behavior(1, [&]()
                             { doAction(LOOK, ""); }, "look");
    Behavior take = Behavior(0.0, [&]()
                             { doAction(TAKE, "food"); }, "take");
    behaviors.push_back(look);
    behaviors.push_back(take);
}

// Listener::Listener(Bot &bot)
// {
//     behaviors.emplace_back(0.5, [&]()
//                            { bot.searchAndTake(); }, "searchRessource");
//     behaviors.emplace_back(0.3, [&]()
//                            { bot.LevelUp(); }, "levelUp");
//     behaviors.emplace_back(0.2, [&]()
//                            { bot.survive(); }, "survive");
// }

Bot::~Bot()
{
}

void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Bot::group()
{
    sendMessage("Group");
}

void Bot::run(std::string response)
{
    printColor("Bot listens: " + response, GREEN);

    listen(response);      // -> change le state
    updateProbabilities(); // -> update les probabilités avec le state
    act();                 // -> fait l'action la plus rentable
}

void Bot::updateProbabilities()
{
    behaviors[0].probability = // has forwaded && is rock searched found etc
        behaviors[1].probability = state.ressources.food * 0.2;
}

void Bot::act()
{
    // behavior more worth.act();
}

void Bot::listen(std::string response)
{
    if (state.lastAction.action == LOOK)
    {
        listenLookResponse(response);
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

void Bot::survive()
{
    printf("Survive\n");
    doAction(FORWARD, "");
    /*params[0] = "food";
    printf("Bot is surviving\n");
    searchAndTake();*/
}

bool Bot::canLvlUp(int lvl)
{
    if (lvl < 2 || lvl > 8)
        return false;

    const auto requirements = levelRequirements[lvl];

    bool hasRequiredResources =
        state.ressources.linemate >= requirements[0] &&
        state.ressources.deraumere >= requirements[1] &&
        state.ressources.sibur >= requirements[2] &&
        state.ressources.mendiane >= requirements[3] &&
        state.ressources.phiras >= requirements[4] &&
        state.ressources.thystame >= requirements[5];

    if (hasRequiredResources)
    {
        return true;
    }
    return false;
}

void Bot::searchAndTake()
{
    /*if (params[0] == "food" && _environement.ressources[0].food >= 1)
    {
        doAction(TAKE, "food");
    }
    else if (params[0] == "linemate" && _environement.ressources[0].linemate >= 1)
    {
        doAction(TAKE, "linemate");
    }
    else
    {
        doAction(FORWARD, "");
    }*/
    printf("SearchAndTake\n");
    doAction(FORWARD, "");
}

void Bot::LevelUp()
{
    /*if (canLvlUp(_lvl + 1)) {
        doAction(INCANTATION, "");
    }*/
    printf("LevelUp\n");
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
    _shouldListen = true;
}
