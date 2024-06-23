/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPatternUtils.hpp
*/

#include "../ABotPattern.hpp"

void ABotPattern::separateServerBroadcast(const std::string &response, std::string &responseServer, std::string &responseBroadcast)
{
    std::istringstream stream(response);
    std::string line;

    while (std::getline(stream, line))
    {
        if (line.find("message") != std::string::npos)
        {
            responseBroadcast += line + "\n";
        }
        else
        {
            responseServer += line + "\n";
        }
    }

    responseServer = cleanCarriageReturn(responseServer);
    responseBroadcast = cleanCarriageReturn(responseBroadcast);

    // Handle encrypted message
    if (!responseBroadcast.empty())
    {
        std::string signature = getElementAfter(responseBroadcast, ':');

        if (signature != _signature)
        {
            _enemyMessage.content = _message.content;
            std::cout << "Enemy message: " << _enemyMessage.content << std::endl;
            return;
        }
        else
        {
            Message _allyMessage;
            std::string temp = getElementBefore(responseBroadcast, ':');
            _allyMessage.content = getElementAfter(temp, ',');
            _direction = getElementBefore(temp, ',');
            _direction = getElementAfter(_direction, ' ');
            _allyMessage.vigenereDecrypt();
            _alliesMessage.push_back(_allyMessage);
            responseBroadcast = _allyMessage.content;
            // printKeyValueColored("Message", _allyMessage.content);
            // printKeyValueColored("Direction", _direction);
        }
    }
}

// TODO: fix set linemate that can be on negativ, waiter incant. 1 say group 2 say joingroup, 2 say group 1 say joingroup because lvl are not updated
// If incant == ko, go search rocks