/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** SimpleBot.hpp
*/

#ifndef SLAVE_HPP_
#define SLAVE_HPP_

#include "ABotPattern.hpp"

class Slave : public ABotPattern
{
public:
    void initChild();
    void updateStrategy() override;
};
#endif // SIMPLEBOT_HPP_