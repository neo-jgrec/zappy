/*
** EPITECH PROJECT, 2024
** zappy/ai/BotFactory
** File description:
** BotFactory.hpp
*/

#ifndef BOTFACTORY_HPP_
#define BOTFACTORY_HPP_

#include "../bots/BotProbabilistic.hpp"
#include <memory>

class BotFactory
{
public:
    static std::unique_ptr<IBot> createBot(const std::string &type);
};

#endif // BOTFACTORY_HPP_
