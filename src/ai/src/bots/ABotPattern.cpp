/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPattern.hpp
*/

#include "ABotPattern.hpp"

void ABotPattern::init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port, int id, int idMessage)
{
    _sockfd = sockfd;
    _teamName = teamName;
    _host = host;
    _port = port;
    _id = id;
    _currentMessageId = idMessage;
    initChild();
    saveActionsFile += teamName + std::to_string(id) + ".txt";
}

void ABotPattern::run(const std::string &response)
{
    std::string responseServer = "";
    std::string responseBroadcast = "";
    _message.content = "";

    // separe servers and broadcast, decrypt message
    separateServerBroadcast(response, responseServer, responseBroadcast);

    verifyServerIsRunning(response);
    debugBotRun();

    // Debug
    debugResponses(responseServer, responseBroadcast);

    if (!responseServer.empty())
    {
        listen(responseServer);
        _canAct = true;
    }
    listenBroadcast(responseBroadcast);
    if (_canAct)
    {
        if (_state.state != SHOULD_GROUP) // TODO: find a cleaner way
            act();
        _canAct = false;
    }
    else if (!responseBroadcast.empty() && _state.state == SHOULD_GROUP)
    {
        act();
    }
    debugState();
    _iteration++;
}

void ABotPattern::act()
{
    if (_state.state != INCANTATING)
    {
        if (queue.empty())
        {
            updateStrategy();
        }
        if (!queue.empty())
        {
            queue.front().first();
            queue.erase(queue.begin());
        }
        if (_iteration % 20 == 0)
            saveDataActions(saveActionsFile);
    }
}

// Always put state listener first before listener for actions
void ABotPattern::listen(const std::string &response)
{
    if (_state.state == INCANTATING)
        listenIncantationReturnResponse(response);
    else if (_state.lastAction.action == LOOK)
        listenLookResponse(response);
    else if (_state.lastAction.action == TAKE)
        listenTakeResponse(response);
    else if (_state.lastAction.action == INCANTATION)
        listenIncantationResponse(response);
    else if (_state.lastAction.action == CONNECT_NBR)
        listenConnectNbrResponse(response);
}

void ABotPattern::listenBroadcast(const std::string &response)
{
    if (response.find("message") != std::string::npos)
    {
        listenBroadcastResponse(response);
    }
}

void ABotPattern::verifyServerIsRunning(const std::string &response)
{
    if (response.empty())
        exit(0);
    if (response.find("dead") != std::string::npos)
    {
        debugState();
        exit(0);
    }
}

// TODO: metrics, save proportions of state in the game, add state: searching, moving, etc...

// Landmaerk: 1. When server need to joing group, when server has response it don't do bot does, that why it make times.
//  Do state that i wrote on paper on the table.