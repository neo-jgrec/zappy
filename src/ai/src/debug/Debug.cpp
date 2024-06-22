/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Debug.cpp
*/
#include "../bots/ABotProbabilistic.hpp"

void ABot::debugInitialisation()
{
    printColor("========== [Bot initiation] ==========\n", BLUE);
    printKeyValueColored("sockfd", std::to_string(_sockfd));
    printKeyValueColored("teamName", _teamName);
    printColor("========== [!Bot initiation] ==========\n\n", BLUE);
}

void ABotProbabilistic::debugTrainedVariables()
{
    printColor("========== [Bot Probabilities] ==========\n", BLUE);

    for (auto &TrainedVariable : _trainedVariables)
    {
        printKeyValueColored(TrainedVariable->name, std::to_string(TrainedVariable->value));
    }
    printColor("========== [!Bot Probabilities] ==========\n", BLUE);
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
    std::cout << std::endl;
}

void ABotPattern::debugResponses(const std::string &responseServer, const std::string &responseBroadcast)
{
    printColor("🤖👂 Bot listens\n", YELLOW);
    printKeyValueColored("\t- server", responseServer);
    printKeyValueColored("\t- broadcast", responseBroadcast);
}

void ABotPattern::debugBotRun()
{
    printColor("========== [Bot Run] ==========\n", BRIGHT_BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    printKeyValueColored("Pattern:", _state.pattern);
}
