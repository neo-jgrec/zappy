/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** LastActions.hpp
*/
// to verify: remove this file.
#ifndef LASTACTION_HPP_
#define LASTACTION_HPP_

#include "Actions.hpp"

class LastAction
{
public:
    LastAction(actions action, std::string parameter);
    ~LastAction();

    actions action;
    std::string parameter;
};

#endif // LASTACTION_HPP_