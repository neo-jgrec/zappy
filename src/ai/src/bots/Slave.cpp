/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Slave.cpp
*/

#include "Slave.hpp"

void Slave::initChild()
{
    std::cout << "🧒✅ Slave initialized" << std::endl;
}

void Slave::updateStrategy()
{
    printf("SLAVE! : ");
    for (auto &_allyMessage : _alliesMessage) {
        if (_allyMessage.content.find("send_ressources") != std::string::npos && _state.level == 2) {
            std::string _msg = "{SLAVE}" + std::to_string(_id) + "/i_have_ressources?" +
            "linemate=" + std::to_string(_state.ressources.linemate) + "|" +
            "deraumere=" + std::to_string(_state.ressources.deraumere) + "|" +
            "sibur=" + std::to_string(_state.ressources.sibur) + "|" +
            "mendiane=" + std::to_string(_state.ressources.mendiane) + "|" +
            "phiras=" + std::to_string(_state.ressources.phiras) + "|" +
            "thystame=" + std::to_string(_state.ressources.thystame) + "&" + std::to_string(_state.level); 
            std::cout << _msg << std::endl;
            _message.format(_msg);
            queue.push_back(std::make_pair([&]()
                                        { doAction(BROADCAST, _message.content); }, "BROADCAST"));
        }
    }
    if (_state.ressources.food < 5) {
        survive();
        return;
    }
    else if (_state.level == 1 && _state.ressources.linemate != 1) {
        searchAndTakeRessource("linemate");
        return;
    }
    else if (_state.ressources.linemate == 1 && _state.level == 1) {
        incantationLvl1();
        return;
    }
}
