/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.hpp
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include "ABotProbabilistic.hpp"
#include "../constant/Constants.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

class Bot : public ABotProbabilistic
{
public:
    void init(int sockfd, const std::string &teamName, bool arg) override;
    void updateProbabilities() override;
    void loadConfig(const std::string &filename);
};
#endif // BOT_HPP_