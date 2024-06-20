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

#include "ABotPattern.hpp"
#include "../pattern/PatternProbabilistic.hpp"
#include "../training/TrainedVariable.hpp"

class ABotProbabilistic : public ABotPattern
{
public:
    ABotProbabilistic();
    ~ABotProbabilistic();
    void run(const std::string &response) override;
    virtual void init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port) = 0;
    // Probabilities
    virtual void updateProbabilities() = 0;

protected:
    bool _doNothing = false;

    std::vector<std::unique_ptr<PatternProbabilistic>> _patterns;
    std::vector<std::unique_ptr<TrainedVariable>> _trainedVariables;

    // Actions
    void updateStrategy() override;

    // Traning
    void normalizeProbabilities();

    // Logic
    bool canLvlUp(int lvl);

    // debug
    void debugTrainedVariables();

    // Probabilities
    const double &getTrainedVariableValueByName(const std::string &name) const;

    // data
    void saveData(const std::string &path) override;
};

#endif // ABOT_PROBABILITIS_HPP_