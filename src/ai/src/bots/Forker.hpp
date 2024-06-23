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
    std::map<int, Ressources> identifyEfficientBots(int currentLevel, NeededResources& neededResources);
    std::pair<NeededResources, std::map<int, Ressources>> calculateAndPrintBotDeposits(std::map<int, Ressources>& sharedInventory, int currentLevel, NeededResources& neededResources);
    std::map<int, Ressources> combineInventories(const std::map<int, Ressources>& inventory1, const std::map<int, Ressources>& inventory2);
    std::string formatBotContributions(const std::map<int, Ressources>& botContributions, const std::map<int, Ressources>& botContributions2);

private:
    unsigned int _idBot = 1;

    void forkNewBot();
    std::map<int, Ressources> sharedInventory;
    std::map<int, Ressources> evoBotInventory;
    BotState _evoBot;
    bool handleSurvive();
};

#endif // FORKER_HPP_