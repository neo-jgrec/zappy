/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** IBot.hpp
*/

#ifndef IBOT_HPP_
#define IBOT_HPP_

#include <iostream>

class IBot
{
public:
    virtual ~IBot() = default;
    virtual void run(const std::string &response) = 0;
    virtual void init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port, int id, int idMessage) = 0;
};

#endif // IBOT_HPP_
