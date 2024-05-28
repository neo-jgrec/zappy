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
    buildDecisionTree();
}

Bot::~Bot()
{
}

// to verify: implement strategy
void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

void Bot::group()
{
    sendMessage("Group");
}

void Bot::buildDecisionTree()
{
    auto forkNode = std::make_shared<DecisionNode>();
    forkNode->condition = [this]() { 
        return true; 
    };
    forkNode->actionIfTrue = actions::FORK;
    forkNode->trueBranch = nullptr;
    forkNode->falseBranch = nullptr;

    auto lookNode = std::make_shared<DecisionNode>();
    lookNode->condition = [this]() { 
        return _inventory.food < 10;
    };
    lookNode->actionIfTrue = actions::LOOK;
    lookNode->trueBranch = nullptr;
    lookNode->falseBranch = nullptr;

    auto root = std::make_shared<DecisionNode>();
    root->condition = [this]() {
        return _lastAction.action == DEFAULT;
    };
    root->actionIfTrue = actions::LOOK;
    root->trueBranch = lookNode;
    root->falseBranch = forkNode;

    decisionTreeRoot = root;
    currentDecisionNode = decisionTreeRoot;
}

void Bot::makeDecision()
{
    while (currentDecisionNode) {
        if (currentDecisionNode->condition()) {
            doAction(currentDecisionNode->actionIfTrue, "");
            currentDecisionNode = currentDecisionNode->trueBranch;
        } else {
            doAction(currentDecisionNode->actionIfFalse, "");
            currentDecisionNode = currentDecisionNode->falseBranch;
        }
    }
    currentDecisionNode = decisionTreeRoot;
}

void Bot::run(std::string response)
{
    printColor("Bot listens: " + response, GREEN);

    /*if (_lastAction.action == DEFAULT)
        takeFirstDecision(response);
    else
        survive(response);*/    
    makeDecision();
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

void Bot::survive(std::string response)
{
    if (_lastAction.action == FORWARD)
    {
        doAction(LOOK, "");
        return;
    }
    if (_inventory.food < 10)
        searchAndTake(response, "food");
    else
        searchAndTake(response, "linemate");
}

void Bot::listenLookResponse(const std::string &response)
{
    // Remove brackets
    std::string cleanedResponse = response.substr(1, response.size() - 2);

    std::istringstream iss(cleanedResponse);
    std::string firstTile;
    std::getline(iss, firstTile, ',');

    _environement.food = 0;
    _environement.linemate = 0;
    _environement.deraumere = 0;
    _environement.sibur = 0;
    _environement.mendiane = 0;
    _environement.phiras = 0;
    _environement.thystame = 0;
    _environement.players = 0;

    std::map<std::string, size_t&> itemMap = {
        {"food", _environement.food},
        {"linemate", _environement.linemate},
        {"deraumere", _environement.deraumere},
        {"sibur", _environement.sibur},
        {"mendiane", _environement.mendiane},
        {"phiras", _environement.phiras},
        {"thystame", _environement.thystame},
        {"player", _environement.players}
    };

    std::istringstream tileStream(firstTile);
    std::string item;

    while (tileStream >> item)
    {
        auto it = itemMap.find(item);
        if (it != itemMap.end())
        {
            it->second += 1;
        }
    }
    _shouldListen = false;
}

// to verify:: do listenTakeResponse
//  to verify: do fonction listen where _shoudlListen = false;
// to verify: do forwardAction that actualise environement
void Bot::searchAndTake(std::string response, const std::string &item)
{
    if (_shouldListen)
        listenLookResponse(response);
    if (item == "food" && _environement.food >= 1)
    {
        doAction(TAKE, "food");
    }
    else if (item == "linemate" && _environement.linemate >= 1)
    {
        doAction(TAKE, "linemate");
    }
    else
    {
        doAction(FORWARD, "");
    }
}

void Bot::doAction(actions action, const std::string &parameter)
{
    ActionInfo actionInfo = getActionInfo(action);

    std::string finalAction = actionInfo.getName();

    if (parameter != "")
        finalAction += " " + parameter;
    printColor("Bot does: " + finalAction, YELLOW);
    sendMessage(finalAction);
    _lastAction.action = action;
    _lastAction.parameter = parameter;
    // to verify: store a paramter, TAKE LINEMATE -> ok -> +1 linemate
    _timeUnit -= actionInfo.getValue();
    if (_timeUnit % 126 == 0)
        _inventory.food -= 1;
    _shouldListen = true;
}
