/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotState.cpp
*/

#include "BotState.hpp"

std::map<Job, std::string> jobMap = {
    {FORKER, "FORKER"},
    {SIMPLE_BOY, "SIMPLE_BOY"},
};

BotState::BotState() : lastAction(actions::DEFAULT, ""), lastBehavior("")
{
}

BotState::~BotState()
{
}
