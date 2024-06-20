/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** SimpleBot.hpp
*/

#ifndef SIMPLEBOT_HPP_
#define SIMPLEBOT_HPP_

#include "ABotPattern.hpp"

class SimpleBot : public ABotPattern
{
public:
    void initChild();
    void updateStrategy() override;
};
#endif // SIMPLEBOT_HPP_