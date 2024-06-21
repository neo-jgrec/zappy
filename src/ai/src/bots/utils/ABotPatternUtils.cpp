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
}
