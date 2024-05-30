/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _id(0), _messageId(0), _lastMessageGuard(""), _lastAction(DEFAULT, ""), _timeUnit(126), _shouldListen(false)
{
    printColor("===== [Bot initiation] =====", GREEN);
    printColor("sockfd: " + std::to_string(_sockfd), YELLOW);
    printColor("teamName: " + _teamName, YELLOW);
    printColor("id: " + std::to_string(_id), YELLOW);
    printColor("messageId: " + std::to_string(_messageId), YELLOW);
    printColor("lastMessageGuard: " + _lastMessageGuard, YELLOW);
    printColor("lastAction: " + std::to_string(_lastAction.action), YELLOW);
    printColor("timeUnit: " + std::to_string(_timeUnit), YELLOW);
    printColor("===== [!Bot initiation] =====", GREEN);
    std::cout << std::endl;

    sendMessage(teamName);
    _inventory.food = 9;
}

Listener::Listener(Bot &bot)
{
    behaviors.emplace_back(0.5, [&]() { bot.searchAndTake(); }, "searchRessource");
    behaviors.emplace_back(0.3, [&]() { bot.LevelUp(); }, "levelUp");
    behaviors.emplace_back(0.2, [&]() { bot.survive(); }, "survive");
}

Bot::~Bot()
{
}

void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Bot::group()
{
    sendMessage("Group");
}

void Bot::run(std::string response)
{
    printColor("Bot listens: " + response, GREEN);

    Listener listener(*this);

    listener.listen(response, *this);
    listener.updateProbabilities(*this);
    listener.act(*this);
}

void Listener::listen(std::string response, Bot &bot)
{
    if (bot._lastAction.action == LOOK) {
        bot._environement.ressources.clear();
        std::string cleanedResponse = response.substr(1, response.size() - 2);

        std::istringstream iss(cleanedResponse);
        std::string tile;

        while (std::getline(iss, tile, ',')) {
            Ressources tileResources;
            std::istringstream tileStream(tile);
            std::string resource;

            while (tileStream >> resource) {
                tileResources.addRessource(resource);
            }
            bot._environement.ressources.push_back(tileResources);
        }
    }
    if (bot._lastAction.action == FORWARD) {

    }
}

void Listener::updateProbabilities(Bot &bot)
{
    auto accumulateResource = [&](auto member) {
        return std::accumulate(bot._environement.ressources.begin(), bot._environement.ressources.end(), 0, [&](int sum, const Ressources& tile) {
            return sum + tile.*member;
        });
    };

    int totalFood = accumulateResource(&Ressources::food);
    int totalLinemate = accumulateResource(&Ressources::linemate);
    int totalDeraumere = accumulateResource(&Ressources::deraumere);
    int totalSibur = accumulateResource(&Ressources::sibur);
    int totalMendiane = accumulateResource(&Ressources::mendiane);
    int totalPhiras = accumulateResource(&Ressources::phiras);
    int totalThystame = accumulateResource(&Ressources::thystame);

    for (auto& behavior : behaviors) {
        behavior.probability = 0.0;
    }

    std::vector<Rule> rules = {
        { 
            [&] { 
                return totalFood < 5;
            },
            [&] {
                for (auto& behavior : behaviors) {
                    if (behavior.name == "survive") {
                        behavior.probability += 0.5;
                    }
                }
            }
        },
        { 
            [&] {
                return bot.canLvlUp(bot._lvl + 1);
            },
            [&] {
                for (auto& behavior : behaviors) {
                    if (behavior.name == "levelUp") {
                        behavior.probability += 0.7;
                    }
                }
            }
        },
        { 
            [&] {
                return totalLinemate >= 1;
            },
            [&] {
                for (auto& behavior : behaviors) {
                    if (behavior.name == "searchRessource") {
                        behavior.probability += 0.9;
                    }
                }
            }
        }
    };

    for (const auto& rule : rules) {
        if (rule.checkCondition()) {
            rule.performAction();
        }
    }

    double totalProbability = std::accumulate(behaviors.begin(), behaviors.end(), 0.0, [](double sum, const Behavior& behavior) {
        return sum + behavior.probability;
    });

    if (totalProbability > 0) {
        for (auto& behavior : behaviors) {
            behavior.probability /= totalProbability;
        }
    }
}

void Listener::act(Bot &bot)
{
    if (!bot.actionQueue.empty()) {
        bot.executeNextAction();
    } else {
        double randomValue = static_cast<double>(rand()) / RAND_MAX;
        std::cout << "Random value: " << randomValue << std::endl;
        double cumulativeProbability = 0.0;

        for (auto& behavior : behaviors) {
            cumulativeProbability += behavior.probability;
            std::cout << "Behavior: " << behavior.name << " - Probability: " << behavior.probability << std::endl;
            if (randomValue <= cumulativeProbability) {
                behavior.act();
                break;
            }
        }
    }
}

void Bot::takeFirstDecision(std::string response)
{
    int slot;
    int x; // to verify: we want to store that in bot ? behavior different if map is larger ?
    int y;

    std::string modifiedInput = response;
    std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
    std::istringstream iss(modifiedInput);
    iss >> slot >> x >> y;

    if (slot == 0)
        doAction(FORK, "");
    else
        doAction(LOOK, "");
}

void Bot::survive()
{
    printf("Survive\n");
    doAction(FORWARD, "");
    /*params[0] = "food";
    printf("Bot is surviving\n");
    searchAndTake();*/
}

bool Bot::canLvlUp(int lvl)
{
    if (lvl < 2 || lvl > 8)
        return false;

    const auto requirements = levelRequirements[lvl];

    bool hasRequiredResources = 
        _inventory.linemate >= requirements[0] &&
        _inventory.deraumere >= requirements[1] &&
        _inventory.sibur >= requirements[2] &&
        _inventory.mendiane >= requirements[3] &&
        _inventory.phiras >= requirements[4] &&
        _inventory.thystame >= requirements[5];

    if (hasRequiredResources) {
        return true;
    }
    return false;
}

void Bot::searchAndTake()
{
    /*if (params[0] == "food" && _environement.ressources[0].food >= 1)
    {
        doAction(TAKE, "food");
    }
    else if (params[0] == "linemate" && _environement.ressources[0].linemate >= 1)
    {
        doAction(TAKE, "linemate");
    }
    else
    {
        doAction(FORWARD, "");
    }*/
    printf("SearchAndTake\n");
    doAction(FORWARD, "");
}

void Bot::LevelUp()
{
    /*if (canLvlUp(_lvl + 1)) {
        doAction(INCANTATION, "");
    }*/
    printf("LevelUp\n");
}

void Bot::doAction(actions action, const std::string &parameter)
{
    ActionInfo actionInfo = getActionInfo(action);
    actionInfo.parameter = parameter;
    actionQueue.push(actionInfo);
}

void Bot::executeNextAction()
{
    if (!actionQueue.empty()) {
        ActionInfo actionInfo = actionQueue.front();
        actionQueue.pop();

        std::string finalAction = actionInfo.getName();
        if (!actionInfo.parameter.empty()) {
            finalAction += " " + actionInfo.parameter;
        }

        printColor("Bot does: " + finalAction, YELLOW);
        sendMessage(finalAction);

        _lastAction.action = actionInfo.getAction();
        _lastAction.parameter = actionInfo.parameter;
        _timeUnit -= actionInfo.getValue();
        if (_timeUnit % 126 == 0) {
            _inventory.food -= 1;
        }
    }
}