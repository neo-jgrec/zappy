/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** SimpleBot.hpp
*/

#ifndef EVOBOT_HPP_
#define EVOBOT_HPP_

#include "ABotPattern.hpp"

class EvoBot : public ABotPattern
{
public:
    void initChild();
    void updateStrategy() override;
};
#endif // SIMPLEBOT_HPP_