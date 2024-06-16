/*
** EPITECH PROJECT, 2024
** zappy/ai/BotFactory
** File description:
** BotFactory.cpp
*/

#include "BotFactory.hpp"

std::unique_ptr<IBot> BotFactory::createBot(const std::string &type)
{
    if (type == "Bot")
    {
        return std::make_unique<Bot>();
    }

    throw std::runtime_error("Invalid bot type: " + type);
}
