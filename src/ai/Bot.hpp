/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot
*/

#ifndef BOT_HPP_
#define BOT_HPP_

#include <iostream>
#include <vector>

class Bot
{
public:
    Bot(unsigned int serverPort);
    ~Bot();

    // Behaviors
    // void listen(); Tom
    // void group(); Quentin
    // void search(); Tom
    // void incant(); Quentin
    // void fork(); Tom
    // void saveInventory(); Quentin
    // void sendMessage(std::string message); Tom

    // Logic
    // void parseMessage(std::string message);
    // void takeDecision(); to override
    // void run(); to override

private:
    unsigned int _serverPort;
    unsigned int _messageId;
    unsigned int _id;
    std::string _lastMessageGuard;
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
