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
#include "actions/Actions.hpp"
#include "environement/Environement.hpp"
#include "ressources/Ressources.hpp"

class LastAction
{
public:
    LastAction(actions action, std::string parameter) : action(action), parameter(parameter) {}
    ~LastAction() {}

    actions action;
    std::string parameter;
};

class Behavior
{
public:
    Behavior();
    ~Behavior();

    double probability;
    std::function<void(void)> act;
};

class Listenener
{
public:
    Listenener();
    ~Listenener();

    std::vector<Behavior> behaviors;
    void listen(std::string response);
    void updateProbabilities();
    Behavior &getWorthBehavior();
    void act();
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

private:
    unsigned int _messageId;
    unsigned int _id;
    std::string _lastMessageGuard;

    // Client
    int _sockfd;
    std::string _teamName;
    LastAction _lastAction;
    Ressources _inventory;
    Environement _environement;

    // Game
    int _timeUnit;
    bool _shouldListen;
    void takeFirstDecision(std::string response);
    void searchAndTake(std::string response, const std::string &item);
    // std::shared_ptr<Node> decisionTreeRoot;
    std::shared_ptr<Node> currentDecisionNode;

    // listen
    void listenLookResponse(const std::string &response);

    // Utils
    void doAction(actions action, const std::string &parameter);

    // Behaviors
    void survive(std::string response);
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
