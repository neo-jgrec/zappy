/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Forker.hpp
*/

#ifndef FORKER_HPP_
#define FORKER_HPP_

#include "ABotPattern.hpp"
#include <sys/wait.h>

class Forker : public ABotPattern
{
public:
    void init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port) override;
    void updateStrategy() override;

private:
    unsigned int _idBot = 1;

    void forkNewBot();
};

#endif // FORKER_HPP_