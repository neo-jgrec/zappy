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

// to verify: make a map with actions name and durability
//  food -= action name.
enum actions
{
    DEFAULT,
    FORWARD,
    RIGHT,
    LEFT,

    LOOK,
    INVENTORY,
    BROADCAST,

    CONNECT_NBR,
    FORK,
    EJECT,

    TAKE,
    SET,
    INCANT
};

class Bot
{
public:
    Bot(int sockfd, std::string teamName);
    ~Bot();

    // Behaviors
    // void listen(); Tom
    // void group(); Quentin
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
    actions _lastAction;
    std::string _nextMove; // to verify: we want to do that anotherway ? Like don't make a listen & react but run or takedecision function
    // inventory map food: 0, linemate: 0, deraumere: 0, sibur: 0, mendiane: 0, phiras: 0, thystame: 0
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
