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

BotState::BotState() : lastAction(actions::DEFAULT, ""), lastPattern("")
{
}

BotState::~BotState()
{
}
