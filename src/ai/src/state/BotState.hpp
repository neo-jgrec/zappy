/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotState.hpp
*/

#ifndef BOTSTATE_HPP_
#define BOTSTATE_HPP_

#include "../environement/Environement.hpp"
#include "../ressources/Ressources.hpp"
#include "../actions/LastAction.hpp"
#include "../behaviors/Behavior.hpp"
#include "../training/Probability.hpp"

#include <vector>
#include <memory>
class BotState
{
public:
    BotState();
    ~BotState();

    Environement environment;
    Ressources ressources;
    LastAction lastAction;
    std::string lastBehavior;
    unsigned int level;

    std::vector<std::string> exploredProbabilities;
};

#endif // BOTSTATE_HPP_