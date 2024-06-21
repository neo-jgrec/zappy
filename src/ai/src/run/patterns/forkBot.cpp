/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** forkBot.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::forkBot(unsigned int idBot)
{
    queue.push_back({[&]()
                     { doAction(CONNECT_NBR, ""); }, "CONNECT_NBR"});
    queue.push_back({[&]()
                     { doAction(FORK, ""); }, "FORK"});
    _message.content = "you are new bot " + std::to_string(idBot);
    queue.push_back({[&]()
                     { doAction(BROADCAST, _message.content); }, "BROADCAST"});
}
