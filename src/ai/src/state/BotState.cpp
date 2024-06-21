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
    {INVOCATING, "INVOCATING"},
    {FORKED, "FORKED"},
};

BotState::BotState() : lastAction("", 0)
{
}

BotState::~BotState()
{
}

const std::string getStateName(State state)
{
    return stateMap[state];
}