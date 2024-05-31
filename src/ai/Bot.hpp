/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.hpp
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include <iostream>
#include <vector>
#include <sys/socket.h>
#include "utils/PrintColor.hpp"
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <queue>

#include "../state/BotState.hpp"
#include "../behaviors/Behavior.hpp"
class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    void group();
    void sendMessage(const std::string &message);
    void run(std::string response);
    void searchAndTake();
    // Paterns
    void LevelUp();
    void survive();
    bool canLvlUp(int);

    std::queue<ActionInfo> actionQueue;
    void executeNextAction();

    // NEW WAY WITH ACTIONS AND PROBABILITIES
    BotState state;
    std::vector<Behavior> behaviors;

    void listen(std::string response);
    void updateProbabilities();
    void act();

private:
    unsigned int _messageId;
    std::vector<std::string> params;

    // Client
    int _sockfd;
    std::string _teamName;

    // Game
    int _timeUnit;
    bool _shouldListen;
    void takeFirstDecision(std::string response);
    void doAction(actions action, const std::string &parameter);

    // listeners
    void listenLookResponse(const std::string &response);

    // Behaviors

    const std::array<std::array<int, 6>, 9> levelRequirements = {{
        {0, 0, 0, 0, 0, 0}, // Level 0
        {0, 0, 0, 0, 0, 0}, // Level 1
        {1, 0, 0, 0, 0, 0}, // Level 2
        {1, 1, 1, 0, 0, 0}, // Level 3
        {2, 0, 1, 0, 2, 0}, // Level 4
        {1, 1, 2, 0, 1, 0}, // Level 5
        {1, 2, 1, 3, 0, 0}, // Level 6
        {1, 2, 3, 0, 1, 0}, // Level 7
        {2, 2, 2, 2, 2, 1}  // Level 8
    }};
};

// RULES
class Rule
{
public:
    using Condition = std::function<bool()>;
    using Action = std::function<void()>;

    Rule(Condition condition, Action action) : condition(condition), action(action) {}

    bool checkCondition() const { return condition(); }
    void performAction() const { action(); }

private:
    Condition condition;
    Action action;
};

#endif // BOT_HPP_
