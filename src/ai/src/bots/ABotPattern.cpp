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
    std::string responseBroadcast = "no message";

    // Mean server crashed
    if (response.empty())
        exit(0);
    // separe servers and broadcast
    separateServerBroadcast(response, responseServer, responseBroadcast);
    _message.content = "";
    printKeyValueColored("🤖👂 Bot listens: ", "server: " + responseServer + ", message: " + responseBroadcast);
    if (!responseServer.empty())
    {
        listen(responseServer);
        _canAct = true;
    }
    listenBroadcast(responseBroadcast);
    if (_canAct)
    {
        act();
        _canAct = false;
    }
    if (responseServer.find("dead") != std::string::npos)
    {
        debugState();
        exit(0);
    }
    debugState();
}

void ABotPattern::act()
{
    printColor("========== [Bot Run] ==========\n", BRIGHT_BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    printKeyValueColored("Pattern:", _state.pattern);

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
        _iteration++;
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

// TODO: metrics, save proportions of state in the game, add state: searching, moving, etc...