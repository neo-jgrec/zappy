/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include "Bot.hpp"

Bot::Bot(int sockfd, std::string teamName) : _sockfd(sockfd), _teamName(teamName), _id(0), _messageId(0), _lastMessageGuard(""), _lastAction(DEFAULT)
{
    printColor("===== [Bot initiation] =====", GREEN);
    printColor("sockfd: " + std::to_string(_sockfd), YELLOW);
    printColor("teamName: " + _teamName, YELLOW);
    printColor("id: " + std::to_string(_id), YELLOW);
    printColor("messageId: " + std::to_string(_messageId), YELLOW);
    printColor("lastMessageGuard: " + _lastMessageGuard, YELLOW);
    printColor("lastAction: " + std::to_string(_lastAction), YELLOW);
    printColor("===== [!Bot initiation] =====", GREEN);
    std::cout << std::endl;

    sendMessage(teamName);
}

Bot::~Bot()
{
}

// to verify: implement strategy
void Bot::sendMessage(const std::string &message)
{
    std::string messageToSend = message + "\n";

    printColor("Bot does: " + message, YELLOW);

    send(_sockfd, messageToSend.c_str(), messageToSend.size(), 0);
}

// to verify: we can calculate by ourself the food
void Bot::run(std::string response)
{
    printColor("Bot listens: " + response, GREEN);

    // First action
    if (_lastAction == DEFAULT)
    {
        int slot;
        int x; // to verify: we want to store that in bot ? behavior different if map is larger
        int y;

        std::string modifiedInput = response;
        std::replace(modifiedInput.begin(), modifiedInput.end(), '\n', ' ');
        std::istringstream iss(modifiedInput);
        iss >> slot >> x >> y;

        if (slot == 0)
        {
            sendMessage("Fork");
            _lastAction = FORK;
        }
        else
        {
            sendMessage("Forward");
            _lastAction = FORWARD; // to verify: make it better with functions
        }
    }
    else if (_lastAction == FORWARD)
    {
        sendMessage("Look");
        _lastAction = LOOK;
    }
    else if (_lastAction == LOOK)
    {
        sendMessage("Inventory");
        _lastAction = INVENTORY;
    }

    // parseMessage(response);
    // takeDecision();

    // analyse then react
}
