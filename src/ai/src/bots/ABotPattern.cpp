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
    // Mean server crashed
    if (response.empty())
        exit(0);
    std::string responseCopy = cleanCarriageReturn(response);

    _message.content = "";
    printKeyValueColored("🤖👂 Bot listens: ", responseCopy);
    if (isServerResponse(responseCopy))
    {
        listen(responseCopy);
        _canAct = true;
    }
    listenBroadcast(responseCopy);
    if (_canAct)
    {
        act();
        _canAct = false;
    }
    if (responseCopy.find("dead") != std::string::npos)
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

    if (_state.state != INVOCATING)
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
    if (_state.state == INVOCATING)
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

bool ABotPattern::isServerResponse(const std::string &response) const
{
    return response.find("message") == std::string::npos;
    // TODO: if message concat with server response do that:
    //  std::vector<std::string> responses = {"ok", "ko", "dead", "[", "]", "Elevation underway", "Current level:"};

    // for (const auto &res : responses)
    // {
    //     if (response.find(res) != std::string::npos)
    //         return true;
    // }
    // if (std::all_of(response.begin(), response.end(), ::isdigit))
    //     return true;
    // return false;
}
