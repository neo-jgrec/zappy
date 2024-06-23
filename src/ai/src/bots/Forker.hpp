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
    void initChild() override;
    void updateStrategy() override;

private:
    unsigned int _idBot = 1;

    void forkNewBot();
    bool handleSurvive();
};

#endif // FORKER_HPP_