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

    std::vector<std::function<void()>> queue;

    // It is what ia observe to adjust behaviors probabilities
    BotState state;
    std::vector<std::unique_ptr<Behavior>> behaviors;
    std::vector<std::unique_ptr<Probability>> probabilities;

    void listen(std::string response);
    void applyReward();
    void act();

    // Traning
    void updateProbabilities();
    void normalizeProbabilities();
    void exploreProbabilities();

    // Debug
    void debugInitialisation();
    void debugProbabilities();
    Probability &getProbabilityByName(const std::string &name);

private:
    unsigned int _messageId;
    unsigned int _iteration;

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
    void listenTakeResponse(const std::string &response);
    void listenForwardResponse(const std::string &response);

    // paterns
    void testPatern();
    void testPatern2();
};

#endif // BOT_HPP_
