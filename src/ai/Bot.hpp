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
#include "actions/Actions.hpp"
#include "environement/Environement.hpp"
#include "ressources/Ressources.hpp"

class Listener;

class LastAction
{
public:
    LastAction(actions action, std::string parameter) : action(action), parameter(parameter) {}
    ~LastAction() {}

    actions action;
    std::string parameter;
};

class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    // Behaviors
    // void listen(); Tom
    void group();
    // void search(); Tom
    // void incant(); Quentin
    // void fork(); Tom
    // void saveInventory(); Quentin
    void sendMessage(const std::string &message); // Tom

    // Logic
    // void parseMessage(std::string message);
    // void takeDecision(); to override
    // void listen(std::string response);
    // void act(); // to override
    void run(std::string response);
    Environement _environement;
    LastAction _lastAction;
    void searchAndTake();
    void LevelUp();
    void survive();
    bool canLvlUp(int); // Quentin
    Ressources _inventory;
    unsigned int _lvl;
    std::queue<ActionInfo> actionQueue;
    void executeNextAction();

private:
    unsigned int _messageId;
    unsigned int _id;
    std::string _lastMessageGuard;
    std::vector<std::string> params;

    // Client
    int _sockfd;
    std::string _teamName;

    // Game
    int _timeUnit;
    bool _shouldListen;
    void takeFirstDecision(std::string response);
    // std::shared_ptr<Node> decisionTreeRoot;

    // listen
    void listenLookResponse(const std::string &response);

    // Utils
    void doAction(actions action, const std::string &parameter);

    // Behaviors

    const std::array<std::array<int, 6>, 9> levelRequirements = {{
        {0, 0, 0, 0, 0, 0},  // Level 0
        {0, 0, 0, 0, 0, 0},  // Level 1
        {1, 0, 0, 0, 0, 0},  // Level 2
        {1, 1, 1, 0, 0, 0},  // Level 3
        {2, 0, 1, 0, 2, 0},  // Level 4
        {1, 1, 2, 0, 1, 0},  // Level 5
        {1, 2, 1, 3, 0, 0},  // Level 6
        {1, 2, 3, 0, 1, 0},  // Level 7
        {2, 2, 2, 2, 2, 1}   // Level 8
    }};
};

class Behavior
{
public:
    Behavior(double probability, std::function<void()> act, std::string name) : probability(probability), act(act), name(name) {};
    Behavior() {};
    ~Behavior() {};

    double probability;
    std::function<void()> act;
    std::string name;
};

class Rule {
public:
    using Condition = std::function<bool()>;
    using Action = std::function<void()>;

    Rule(Condition condition, Action action) : condition(condition), action(action) {}

    bool checkCondition() const { return condition(); }
    void performAction() const { action(); }

private:
    Condition condition;
    Action action;
};


class Listener
{
public:
    Listener(Bot &bot);
    ~Listener() {}

    std::vector<Behavior> behaviors;
    LastAction _lastAction = LastAction(DEFAULT, "");

    void listen(std::string response, Bot &bot);

    void updateProbabilities(Bot &bot);

    void printEnvironment(Environement &_environement) {
        int i = 0;

        for (auto &tile : _environement.ressources) {
            std::cout << "-----------------------tile: " << i << "-----------------------------" << std::endl;
            std::cout << "food: " << tile.food << std::endl;
            std::cout << "linemate: " << tile.linemate << std::endl;
            std::cout << "deraumere: " << tile.deraumere << std::endl;
            std::cout << "sibur: " << tile.sibur << std::endl;
            std::cout << "mendiane: " << tile.mendiane << std::endl;
            std::cout << "phiras: " << tile.phiras << std::endl;
            std::cout << "thystame: " << tile.thystame << std::endl;
            std::cout << "-----------------------tile: " << i << "-----------------------------" << std::endl;
            i++;
        }
    }
    Behavior& getWorthBehavior() {
        return *std::max_element(behaviors.begin(), behaviors.end(),
            [](const Behavior& a, const Behavior& b) {
                return a.probability < b.probability;
            });
    }

    void act(Bot &bot);
};


#endif // BOT_HPP_

/*
LIST MESSAGES + BEHAVIORS:

IF 1 LINEMATE
EVOLVE

IF CAN TAKE LVL 2
SAY GROUP FOR EVERY IA LVL 1 COME.
WHEN ALL PLAYERS COME TO THE TILE SAY INCANTATION

INCANTATION:
IA MUST SAY WHEN THEY LEVELED UP

GUARD {
    NB_IA,
    ARRAY_IA WITH THEIR LVL,
}

message des IA  : signature, message, id_msg
message du guard : signature, guard, message, id_msg

*/
