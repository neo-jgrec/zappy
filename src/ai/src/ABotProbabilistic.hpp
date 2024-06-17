/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotProbabilistic.hpp
*/

#ifndef ABOT_PROBABILISTIC_HPP_
#define ABOT_PROBABILISTIC_HPP_

#include "IBot.hpp"
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
#include <cmath>
#include <random>

#include "state/BotState.hpp"
#include "behaviors/Behavior.hpp"
#include "utils/PrintColor.hpp"
#include "message/Message.hpp"
#include "utils/StringUtils.hpp"
#include "IBot.hpp"
#include "hash/Pairhash.hpp"

enum Orientation
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class ABotProbabilistic : public IBot
{
public:
    ABotProbabilistic();
    ~ABotProbabilistic();
    void run(const std::string &response) override;
    virtual void init(int sockfd, const std::string &teamName) = 0;

    // Probabilities
    virtual void updateProbabilities() = 0;

protected:
    // TODO: move
    std::unordered_map<std::pair<int, int>, std::vector<std::string>, PairHash> movementMap = {
        {{-1, 1}, {"FORWARD", "LEFT", "FORWARD"}},
        {{0, 1}, {"FORWARD"}},
        {{1, 1}, {"FORWARD", "RIGHT", "FORWARD"}},
        {{1, 2}, {"RIGHT", "FORWARD", "LEFT", "FORWARD", "FORWARD"}},
        {{1, 3}, {"RIGHT", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{2, 2}, {"RIGHT", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD"}},
        {{2, 3}, {"RIGHT", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{3, 3}, {"RIGHT", "FORWARD", "FORWARD", "FORWARD", "LEFT", "FORWARD", "FORWARD", "FORWARD"}},
        {{0, 2}, {"FORWARD", "FORWARD"}},
        {{-1, 2}, {"LEFT", "FORWARD", "RIGHT", "FORWARD", "FORWARD"}},
        {{-1, 3}, {"LEFT", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{-2, 2}, {"LEFT", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD"}},
        {{-2, 3}, {"LEFT", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{-3, 3}, {"LEFT", "FORWARD", "FORWARD", "FORWARD", "RIGHT", "FORWARD", "FORWARD", "FORWARD"}},
        {{0, 3}, {"FORWARD", "FORWARD", "FORWARD"}},
    };

    bool _doNothing = false;

    // Client
    int _sockfd;
    std::string _teamName;

    // Game
    unsigned int _iteration;
    Orientation _orientation;
    int _timeUnit;

    // Messages
    Message _message;
    std::string direction;
    Message _enemyMessage;
    std::string _signature = "bFNneQbXQkyJHGEQd";

    // Material of training
    BotState _state;
    std::vector<std::unique_ptr<Behavior>> _behaviors;
    std::vector<std::unique_ptr<Probability>> _probabilities;

    // Actions
    std::vector<std::pair<std::function<void()>, std::string>> queue;

    // Interract with server
    void listen(const std::string &response);
    void sendMessage(const std::string &message);

    // Actions
    void act();
    void doAction(actions action, const std::string &parameter);

    // Traning
    void normalizeProbabilities();
    void exploreProbabilities();

    // Listeners
    void listenLookResponse(const std::string &response);
    void listenForkResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenForwardResponse(const std::string &response);
    void listenBroadcastResponse(const std::string &response);

    // Logic
    void findPath(std::pair<int, int> start, const std::pair<int, int> &end);
    void turnToDirection(std::pair<int, int> &pos, Orientation targetDir);
    void moveForward(std::pair<int, int> &pos);
    void turnLeft(std::pair<int, int> &pos);
    void turnRight(std::pair<int, int> &pos);

    // Paterns
    void testPatern();
    void searchAndTake(std::string param);
    void survive();
    void searchAndTakeRessource(const std::string &ressource);
    void group();
    void searchLinemate();
    void searchDeraumere();
    void searchSibur();
    void searchMendiane();
    void searchPhiras();
    void searchThystame();
    void trapMessage();

    // Debug
    void debugInitialisation();
    void debugProbabilities();

    // Probabilities
    Probability &getProbabilityByName(const std::string &name);
};

#endif // ABOT_PROBABILITIS_HPP_
