/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Debug.cpp
*/
#include "../bots/ABotPattern.hpp"

void ABot::debugInitialisation()
{
    printColor("========== [Bot initiation] ==========\n", BLUE);
    printKeyValueColored("sockfd", std::to_string(_sockfd));
    printKeyValueColored("teamName", _teamName);
    printColor("========== [!Bot initiation] ==========\n\n", BLUE);
}

void ABot::debugState()
{
    printColor("🤖📋 Bot State\n", YELLOW);
    printKeyValueColored("food", std::to_string(_state.ressources.food));
    printKeyValueColored("linemate", std::to_string(_state.ressources.linemate));
    printKeyValueColored("deraumere", std::to_string(_state.ressources.deraumere));
    printKeyValueColored("sibur", std::to_string(_state.ressources.sibur));
    printKeyValueColored("mendiane", std::to_string(_state.ressources.mendiane));
    printKeyValueColored("phiras", std::to_string(_state.ressources.phiras));
    printKeyValueColored("thystame", std::to_string(_state.ressources.thystame));
    printKeyValueColored("level", std::to_string(_state.level));
    printKeyValueColored("state", getStateName(_state.state));
}

void ABotPattern::debugResponses(const std::string &responseServer, const std::string &responseBroadcast)
{
    PRINT_STATE state = PRINT_STATE_INFO;
    if (responseServer.find("ok") != std::string::npos)
        state = PRINT_STATE_SUCESS;
    else if (responseServer.find("ko") != std::string::npos)
        state = PRINT_STATE_WARNING;
    printColor("🤖👂 Bot listens\n", YELLOW);
    printKeyValueColored("\t- server", responseServer, state);
    printKeyValueColored("\t- broadcast", responseBroadcast);
}

void ABotPattern::debugBotRun()
{
    printColor("========== [Bot Run] ==========\n", BRIGHT_BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    printKeyValueColored("Pattern:", _state.pattern);
}

void ABotPattern::debugMetadata()
{
    printColor("🤖📂 Bot metadata\n", YELLOW);
    _state.printMetadata();
    std::cout << std::endl;
}

void ABot::debugAction(const ActionInfo actionInfo, const std::string &parameter)
{
    ActionInfo actionToServerClean = actionInfo;
    std::string finalParameter = parameter;

    if (actionInfo.action == BROADCAST)
    {
        if (parameter.empty())
        {
            exit(0);
        }
        else
        {
            std::string tmpStr = getElementBefore(parameter, ':');
            Message tmp(tmpStr);
            tmp.vigenereDecrypt();
            finalParameter = tmp.content;
        }
    }
    std::string actionToServer = actionToServerClean.getName();

    if (!finalParameter.empty())
        actionToServer += " " + finalParameter;
    static int forward = 0;
    if (actionInfo.action == FORWARD)
        forward++;
    printf("forward = %d\n", forward);
    printKeyValueColored("🤖🤜 Bot does", actionToServer);
}
