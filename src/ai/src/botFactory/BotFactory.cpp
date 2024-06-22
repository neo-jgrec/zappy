/*
** EPITECH PROJECT, 2024
** zappy/ai/BotFactory
** File description:
** BotFactory.cpp
*/

#include "BotFactory.hpp"

std::unique_ptr<IBot> BotFactory::createBot(const std::string &type)
{
    if (type == "Forker")
    {
        return std::make_unique<Forker>();
    }
    if (type == "SimpleBot")
    {
        return std::make_unique<SimpleBot>();
    }

    return nullptr;
}
