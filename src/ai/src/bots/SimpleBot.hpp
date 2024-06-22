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

    // Levels
    void handleLvl1();
    void handleLvl2();
    void handleLvl3();

    // State
    bool handleState();

    // Survive
    bool handleSurvive();
};
#endif // SIMPLEBOT_HPP_