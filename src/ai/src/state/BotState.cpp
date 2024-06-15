/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotState.cpp
*/

#include "BotState.hpp"

BotState::BotState() : lastAction(actions::DEFAULT, ""), lastBehavior(""), level(1), reward(0)
{
}

BotState::~BotState()
{
}
