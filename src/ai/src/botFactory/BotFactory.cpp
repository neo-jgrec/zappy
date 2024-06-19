/*
** EPITECH PROJECT, 2024
** zappy/ai/BotFactory
** File description:
** BotFactory.cpp
*/

#include "BotFactory.hpp"

std::unique_ptr<IBot> BotFactory::createBot(const std::string &type)
{
    if (type == "BotProbabilistic")
    {
        return std::make_unique<BotProbabilistic>();
    }

    throw std::runtime_error("Invalid bot type: " + type);
}
