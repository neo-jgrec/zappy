/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotState.cpp
*/

#include "BotState.hpp"

std::map<Job, std::string> jobMap = {
    {FORKER, "FORKER"},
    {SIMPLE_BOT, "SIMPLE_BOT"},
};

std::map<State, std::string> stateMap = {
    {STANDARD, "STANDARD"},
    {FORKED, "FORKED"},
    {WAIT_FOR_SERVER_RESPONSE, "WAIT_FOR_SERVER_RESPONSE"},
    {WAIT_FOR_BROADCAST_RESPONSE, "WAIT_FOR_BROADCAST_RESPONSE"},
    {ACT_ON_SERVER, "ACT_ON_SERVER"},
    {ACT_ON_BROADCAST, "ACT_ON_BROADCAST"},
};

BotState::BotState() : lastAction("", 0)
{
}

BotState::~BotState()
{
}

void BotState::printMetadata() const
{
    for (auto &meta : metadata)
    {
        printKeyValueColored(meta.first, meta.second);
    }
}

const std::string getStateName(State state)
{
    return stateMap[state];
}
