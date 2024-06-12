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

class pairHash
{
public:
    std::size_t operator()(const std::pair<int, int>& p) const {
        auto hash1 = std::hash<int>{}(p.first);
        auto hash2 = std::hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};


class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    void sendMessage(const std::string &message);

    void run(std::string response);

    std::vector<std::pair<std::function<void()>, std::string>> queue;

    std::unordered_map<std::pair<int, int>, std::vector<std::string>, pairHash> movementMap = {
        { {-1, 1}, {"FORWARD", "LEFT", "FORWARD"} },
        { {0, 1},  {"FORWARD"} },
        { {1, 1},  {"FORWARD", "RIGHT", "FORWARD"} },
        { {1, 2},  {"FORWARD", "RIGHT", "FORWARD"} },
        { {0, 2},  {"FORWARD", "FORWARD"} },
        { {1, 2},  {"FORWARD", "FORWARD", "RIGHT"} },
        { {2, 2},  {"FORWARD", "FORWARD", "RIGHT", "RIGHT"} },
        { {0, 3},  {"FORWARD", "FORWARD", "FORWARD"} },
    };

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
    enum Orientation { 
        NORTH,
        EAST, 
        SOUTH,
        WEST 
    };
    Orientation _orientation;
    int x;
    int y;

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

    void findPath(std::pair<int, int> start, const std::pair<int, int> &end);
    void turnToDirection(std::pair<int, int> &pos, Orientation targetDir);
    void moveForward(std::pair<int, int> &pos);
    void turnLeft(std::pair<int, int> &pos);
    void turnRight(std::pair<int, int> &pos);
    // paterns
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
};

#endif // BOT_HPP_
