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

#include <vector>
#include <memory>

enum State
{
    STANDART,
    LISTENING,
    FORKED,
};

enum Job
{
    SEARCH_IDENTITY,
    FORKER,
    SIMPLE_BOY,
};

extern std::map<Job, std::string> jobMap;

class BotState
{
public:
    BotState();
    ~BotState();

    Environement environment;
    Ressources ressources;
    LastAction lastAction;
    std::string lastBehavior;
    State state = STANDART;
    Job job = SEARCH_IDENTITY;
    unsigned int level = 1;
    unsigned int slot = 0;
    unsigned int widthMap = 42;
    unsigned int heightMap = 42;

    std::vector<std::string> exploredProbabilities;
};

#endif // BOTSTATE_HPP_