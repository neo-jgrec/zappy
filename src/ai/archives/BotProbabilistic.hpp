/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.hpp
*/

#ifndef BOT_PROBABILISTIC_HPP_
#define BOT_PROBABILISTIC_HPP_

#include "ABotProbabilistic.hpp"
#include "../constant/Constants.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

class BotProbabilistic : public ABotProbabilistic
{
public:
    void initChild() override;
    void updateProbabilities() override;
    void loadConfig(const std::string &filename);
};
#endif // BOT_PROBABILISTIC_HPP_