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

#include <vector>
#include <memory>
#include <map>

enum State
{
    STANDART,
    INVOCATING,
    FORKED,
};

enum Job
{
    FORKER,
    SIMPLE_BOT,
};

extern std::map<Job, std::string> jobMap;

class BotState
{
public:
    BotState();
    ~BotState();

    Environement environment;
    Ressources ressources;
    State state = STANDART;
    ActionInfo lastAction;

    std::string lastPattern;

    unsigned int level = 1;
    unsigned int slot = 0;
    unsigned int widthMap = 42;
    unsigned int heightMap = 42;

    // Metrics
    std::vector<ActionInfo> actionsData;
};

#endif // BOTSTATE_HPP_