/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Forker.hpp
*/

#ifndef FORKER_HPP_
#define FORKER_HPP_

#include "ABotPattern.hpp"
#include "../constant/Constants.hpp"
#include <sys/wait.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <algorithm>

class Forker : public ABotPattern
{
public:
    void initChild() override;
    void updateStrategy() override;
    Ressources parseRessources(const std::string& ressourcesString);
    std::pair<bool, NeededResources> canLevelUp(int currentLevel);
    std::vector<int> identifyEfficientBots(int currentLevel, const NeededResources& neededResources);

private:
    unsigned int _idBot = 1;

    void forkNewBot();
    std::map<int, Ressources> sharedInventory;
    BotState _evoBot;
};

#endif // FORKER_HPP_