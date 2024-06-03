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

#include "state/BotState.hpp"
#include "behaviors/Behavior.hpp"
class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    void sendMessage(const std::string &message);

    void run(std::string response);

    // It is what ia observe to adjust behaviors probabilities
    BotState state;
    std::vector<Behavior> behaviors;

    void listen(std::string response);
    void act();

private:
    unsigned int _messageId;

    // Client
    int _sockfd;
    std::string _teamName;

    // Game
    int _timeUnit;

    void takeFirstDecision(std::string response);
    void doAction(actions action, const std::string &parameter);

    // listeners
    void listenLookResponse(const std::string &response);
    void listenForkResponse(const std::string &response);

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

#endif // BOT_HPP_
