/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABotPattern.hpp
*/

#include "ABotPattern.hpp"

ABotPattern::ABotPattern()
{
}

void ABotPattern::init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port, int id, int idMessage)
{
    _sockfd = sockfd;
    _teamName = teamName;
    _host = host;
    _port = port;
    _currentMessageId = idMessage;
    initChild();
}

ABotPattern::~ABotPattern()
{
}
// Landmark: 1. Goes from homeless to jobfull. Wait the max limit unit time before going homeless.
void ABotPattern::act()
{
    printColor("========== [Bot Run] ==========\n", BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    if (_state.state != LISTENING)
    {
        if (queue.empty())
            updateStrategy();
        if (!queue.empty())
        {
            queue.front().first();
            queue.erase(queue.begin());
        }
    }
    _iteration++;
    if (_iteration % 20 == 0 && !filenameSave.empty()) // TODO: make it when flag --save-data is entered
    {
        saveData(filenameSave);
    }
    _state.state = STANDART;
}

void ABotPattern::run(const std::string &response)
{
    std::string responseCopy = response;
    static bool _canAct = false;

    _message._content = "";

    if (!responseCopy.empty() && responseCopy.back() == '\n')
    {
        responseCopy.pop_back();
    }
    printKeyValueColored("Bot listens", responseCopy);
    if (responseCopy.find("message") == std::string::npos || responseCopy.find("ok") != std::string::npos || responseCopy.find("ko") != std::string::npos)
    {
        _canAct = true;
        std::cout << "canAct: " << _canAct << std::endl;
    }
    else
    {
        std::cout << "canAct: " << _canAct << std::endl;
    }
    listen(responseCopy);
    // Bot wait for a job
    if (_canAct || _iteration == 0)
    {
        act();
        _canAct = false;
    }
    if (_iteration == 200 || (responseCopy.find("dead") != std::string::npos))
    {
        debugState();
        saveData("./src/ai/dataSaved/behaviors.txt");
        exit(0);
    }
    debugState();
}

void ABotPattern::listen(const std::string &response)
{
    if (_state.lastAction.action == LOOK)
        listenLookResponse(response);
    else if (_state.lastAction.action == TAKE)
        listenTakeResponse(response);
    else if (_state.lastAction.action == INCANTATION)
        listenIncantationResponse(response);
    else if (_state.state == LISTENING)
        listenIncantationReturnResponse(response);
    else if (_state.lastAction.action == CONNECT_NBR)
        listenConnectNbrResponse(response);
    if (response.find("message") != std::string::npos)
    {
        listenBroadcastResponse(response);
    }
}

void ABotPattern::saveData(const std::string &filename)
{
    std::ofstream out(filename, std::ios_base::app);

    out << "iteration:" << _iteration << "\n";
    for (const auto &pattern : _patterns)
    {
        out << pattern->name << ":" << pattern->count << "\n";
    }
    out << "\n";
}

// TODO: we can know the frequence by the time an action take