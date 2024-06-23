/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPattern.hpp
*/

#include "ABotPattern.hpp"
#include <filesystem>
#include <string>

void ABotPattern::init(int sockfd, const std::string &teamName, const std::string &host, int port, int id, int idMessage)
{
    _sockfd = sockfd;
    _teamName = teamName;
    _host = host;
    _port = port;
    _id = id;
    _currentMessageId = idMessage;
    initChild();
    std::string baseFileName = teamName + "-";
    int suffix = 0;
    while (true)
    {
        saveActionsFile += baseFileName + std::to_string(suffix) + ".txt";
        if (!std::filesystem::exists(saveActionsFile))
        {
            break;
        }
        ++suffix;
    }
}

void ABotPattern::run(const std::string &response)
{
    std::string responseServer = "";
    std::string responseBroadcast = "";
    _message.content = "";
    _allyMessage.content = "";
    _enemyMessage.content = "";

    // separe servers and broadcast, decrypt message
    separateServerBroadcast(response, responseServer, responseBroadcast);

    verifyServerIsRunning(response);
    debugBotRun();

    // Debug
    debugResponses(responseServer, responseBroadcast);

    if (!responseServer.empty())
        _canAct = true;

    if (!responseServer.empty() && _state.state != WAIT_FOR_BROADCAST_RESPONSE)
    {
        listen(responseServer);
    }
    if (!responseBroadcast.empty() && _state.state != WAIT_FOR_SERVER_RESPONSE)
    {
        listenBroadcastResponse();
    }
    if (_state.state != WAIT_FOR_BROADCAST_RESPONSE && _state.state != WAIT_FOR_SERVER_RESPONSE)
    {
        react(responseServer, responseBroadcast);
    }
    debugState();
    debugMetadata();
}

void ABotPattern::react(const std::string &responseServer, const std::string &responseBroadcast)
{
    if (_canAct)
    {
        if (!responseServer.empty() && !responseBroadcast.empty())
        {
            PRINT_ALERT("GET RESPONSES FROM SERVER AND BROADCAST\n");
        }
        if (!responseServer.empty() && _state.state != ACT_ON_BROADCAST)
        {
            if (_state.state != ACT_ON_BROADCAST)
                act();
        }
        else if (!responseBroadcast.empty() && _state.state != ACT_ON_SERVER)
        {
            act();
        }
    }
}

void ABotPattern::act()
{
    if (queue.empty())
    {
        updateStrategy();
    }
    if (!queue.empty())
    {
        queue.front().first();
        queue.erase(queue.begin());
        _canAct = false;
        _iteration++;
    }
    if (_iteration % 20 == 0)
        saveDataActions(saveActionsFile);
}

// Always put state listener before listener for actions
void ABotPattern::listen(const std::string &response)
{
    if (_state.state == WAIT_FOR_SERVER_RESPONSE)
        listenCancel(response);
    if (_state.state == WAIT_FOR_SERVER_RESPONSE && isConcernedByIncantation())
        listenIncantationReturnResponse(response);
    else if (_state.lastAction.action == INVENTORY)
        listenInventoryResponse(response);
    else if (_state.lastAction.action == LOOK)
        listenLookResponse(response);
    else if (_state.lastAction.action == TAKE)
        listenTakeResponse(response);
    else if (isConcernedByIncantation())
        listenIncantationResponse(response);
    else if (_state.lastAction.action == CONNECT_NBR)
        listenConnectNbrResponse(response);
}

void ABotPattern::verifyServerIsRunning(const std::string &response)
{
    if (response.find("dead") != std::string::npos)
    {
        debugState();
        PRINT_ALERT("END OF BOT\n");
        exit(0);
    }
}
