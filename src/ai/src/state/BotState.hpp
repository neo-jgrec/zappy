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
#include "../utils/PrintColor.hpp"

#include <vector>
#include <memory>
#include <map>

enum State
{
    STANDARD,
    FORKED,
    WAIT_FOR_SERVER_RESPONSE,    // Do nothing and wait for server response
    WAIT_FOR_BROADCAST_RESPONSE, // Do nothing and wait for broadcast response
    ACT_ON_SERVER,               // Do an action on server
    ACT_ON_BROADCAST,            // Do an action on broadcast
};

enum Job
{
    FORKER,
    SIMPLE_BOT,
    SLAVE,
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
    State prevState = STANDARD;
    ActionInfo lastAction;
    // TODO: to remove, it is to debug
    std::string pattern = "no pattern";

    unsigned int level = 1;
    unsigned int slot = 0;
    unsigned int widthMap = 42;
    unsigned int heightMap = 42;
    unsigned int nbAlly = 0;

    std::map<std::string, std::string> metadata = {
        {"should_update_env", "true"},
        {"should_group", "false"},
        {"should_incant", "false"},
        {"wait_incant", "false"},
        {"ask_for_group",
         "false"},
        {"id_group", "0"},
    };

    // Metrics
    std::vector<ActionInfo>
        actionsData;

    void printMetadata() const;
};

const std::string getStateName(State state);

#endif // BOTSTATE_HPP_