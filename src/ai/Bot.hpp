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
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <queue>
#include <cstdlib>
#include <ctime>

#include "state/BotState.hpp"
#include "behaviors/Behavior.hpp"
#include "utils/PrintColor.hpp"

class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    void sendMessage(const std::string &message);

    void run(std::string response);

    // It is what ia observe to adjust behaviors probabilities
    BotState state;
    std::vector<std::unique_ptr<Behavior>> behaviors;

    void listen(std::string response);
    void act();
    void applyReward();

private:
    unsigned int _messageId;

    // Client
    int _sockfd;
    std::string _teamName;

    // Game
    int _timeUnit;

    void takeFirstDecision(std::string response);
    void doAction(actions action, const std::string &parameter, const std::string &behaviorName);

    // listeners
    void listenLookResponse(const std::string &response);
    void listenForkResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenForwardResponse(const std::string &response);
};

#endif // BOT_HPP_
