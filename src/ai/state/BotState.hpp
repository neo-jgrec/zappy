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
#include "../actions/Actions.hpp"

class BotState
{
public:
    BotState();
    ~BotState();

    Environement environment;
    Ressources ressources;
    LastAction lastAction;
    unsigned int level;
};

#endif // BOTSTATE_HPP_