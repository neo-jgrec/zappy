/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPatternUtils.hpp
*/

#include "../ABotPattern.hpp"

void ABotPattern::separateServerBroadcast(const std::string &response, std::string &responseServer, std::string &responseBroadcast)
{
    size_t messagePos = response.find("message");

    if (messagePos != std::string::npos)
    {
        responseServer = response.substr(0, messagePos);
        responseBroadcast = response.substr(messagePos);
    }
    else
    {
        responseServer = response;
    }
    responseServer = cleanCarriageReturn(responseServer);
    responseBroadcast = cleanCarriageReturn(responseBroadcast);

    // Handle encryted message
    if (responseBroadcast.empty())
        responseBroadcast = "no message";
    else
    {
        std::string signature = getElementAfter(responseBroadcast, ':');

        if (signature != _signature)
        {
            _enemyMessage = _message.content;
            std::cout << "Enemy message: " << _enemyMessage.content << std::endl;
            return;
        }
        else
        {
            std::string temp = getElementBefore(responseBroadcast, ':');
            _allyMessage.content = getElementAfter(temp, ',');
            _direction = getElementBefore(temp, ',');
            _direction = getElementAfter(_direction, ' ');
            _allyMessage.vigenereDecrypt();
            responseBroadcast = _allyMessage.content;
            // printKeyValueColored("Message", _allyMessage.content);
            // printKeyValueColored("Direction", _direction);
        }
    }
}
