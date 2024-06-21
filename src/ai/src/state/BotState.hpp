/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotState.hpp
*/

#ifndef BOTSTATE_HPP_
#define BOTSTATE_HPP_

#include "../environment/Environment.hpp"
#include "../ressources/Ressources.hpp"
#include "../actions/Action.hpp"

#include <vector>
#include <memory>
#include <map>

enum State
{
    STANDARD,
    INCANTATING,
    FORKED,
    SHOULD_GROUP,
};

enum Job
{
    FORKER,
    SIMPLE_BOT,
};

extern std::map<State, std::string> stateMap;
extern std::map<Job, std::string> jobMap;

class BotState
{
public:
    BotState();
    ~BotState();

    Environment environment;
    Ressources ressources;
    State state = STANDARD;
    ActionInfo lastAction;
    // TODO: to remove, it is to debug
    std::string pattern = "no pattern";

    unsigned int level = 1;
    unsigned int slot = 0;
    unsigned int widthMap = 42;
    unsigned int heightMap = 42;

    // Metrics
    std::vector<ActionInfo> actionsData;
};

const std::string getStateName(State state);

#endif // BOTSTATE_HPP_