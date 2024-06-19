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
#include <fstream>

#include "ABot.hpp"
#include "pattern/Pattern.hpp"
#include "training/TrainedVariable.hpp"

class ABotProbabilistic : public ABot
{
public:
    ABotProbabilistic();
    ~ABotProbabilistic();
    void run(const std::string &response) override;
    virtual void init(int sockfd, const std::string &teamName) = 0;

    // Probabilities
    virtual void updateProbabilities() = 0;

protected:
    bool _doNothing = false;

    std::vector<std::unique_ptr<Pattern>> _patterns;
    std::vector<std::unique_ptr<TrainedVariable>> _trainedVariables;

    // Interract with server
    void listen(const std::string &response);

    // Actions
    void act();

    // Traning
    void normalizeProbabilities();

    // Listeners
    void listenLookResponse(const std::string &response);
    void listenForkResponse(const std::string &response);
    void listenTakeResponse(const std::string &response);
    void listenForwardResponse(const std::string &response);
    void listenBroadcastResponse(const std::string &response);
    void listenIncantationResponse(const std::string &response);
    void listenIncantationReturnResponse(const std::string &response);

    // Logic
    void findPath(std::pair<int, int> start, const std::pair<int, int> &end);
    void turnToDirection(std::pair<int, int> &pos, Orientation targetDir);
    void moveForward(std::pair<int, int> &pos);
    void turnLeft(std::pair<int, int> &pos);
    void turnRight(std::pair<int, int> &pos);

    // Paterns
    void testPatern();
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
    void incantation(std::vector<std::string> objs);

    // debug
    void debugTrainedVariables();

    // Probabilities
    const double &getTrainedVariableValueByName(const std::string &name) const;

    // data
    void saveData(const std::string &path);
};

#endif // ABOT_PROBABILITIS_HPP_
