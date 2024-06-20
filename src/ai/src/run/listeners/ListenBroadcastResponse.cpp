/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ListenBroadcastResponse.cpp
*/

#include "../../bots/ABotPattern.hpp"

void ABotPattern::listenJob()
{
    std::string job = "";
    std::string prefixId = "you_are_bot_";
    std::string prefixJob = "job_is_";
    size_t pos = _allyMessage._content.find(prefixId);
    size_t posJob = _allyMessage._content.find(prefixJob);

    if (pos != std::string::npos)
    {
        std::string idStr = _allyMessage._content.substr(pos + prefixId.size());
        _id = std::stoi(idStr);
    }
    if (posJob != std::string::npos)
    {
        job = _allyMessage._content.substr(posJob + prefixJob.size());
        if (job == "FORKER")
            _state.job = FORKER;
        else if (job == "SIMPLE_BOY")
            _state.job = SIMPLE_BOY;
    }
}

void ABotPattern::listenBroadcastResponse(const std::string &response)
{
    std::string signature = getElementAfter(response, ':');

    if (signature != _signature)
    {
        _enemyMessage = _message._content;
        std::cout << "Enemy message: " << _enemyMessage._content << std::endl;
        return;
    }
    else
    {
        std::string temp = getElementBefore(response, ':');
        _allyMessage._content = getElementAfter(temp, ',');
        direction = getElementBefore(temp, ',');
        direction = getElementAfter(direction, ' ');
        _allyMessage.vigenereDecrypt();
        printKeyValueColored("Message", _allyMessage._content);
        printKeyValueColored("Direction", direction);
        if (_allyMessage._content.find("you_are_bot_") != std::string::npos)
        {
            listenJob();
        }
    }
}
