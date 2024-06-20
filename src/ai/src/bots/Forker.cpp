/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Forker.cpp
*/

#include "Forker.hpp"

void Forker::init(int sockfd, const std::string &teamName, bool arg, const std::string &host, int port)
{
    _sockfd = sockfd;
    _teamName = teamName;
    sendMessage(teamName);
    _host = host;
    _port = port;
}

void Forker::forkNewBot()
{
    pid_t pid = fork();

    if (pid == -1)
    {
        std::cerr << "Fork failed" << std::endl;
        return;
    }

    if (pid == 0)
    {
        // execl("./zappy_ai", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);
        execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        std::cerr << "execl failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        _message.format("you_are_bot_" + std::to_string(_idBot) + "_and_your_job_is_" + jobMap[SIMPLE_BOY]);
        queue.push_back(std::make_pair([&]()
                                       { doAction(BROADCAST, _message._content); }, "FORK"));

        wait(nullptr);
    }
}

void Forker::updateStrategy()
{
    static bool canFork = true; // TODO: it is to debug
    static int timeToKnowHisIdentity = 0;

    if (_state.job == SEARCH_IDENTITY)
    {
        _message.format("I'm_searching_my_identity_🤔");
        queue.push_back(std::make_pair([&]()
                                       { doAction(BROADCAST, _message._content); }, "BROADCAST"));
        timeToKnowHisIdentity++;
    }
    else if (_state.job != FORKER)
    {

        std::cout << "I'm the bot: " << std::to_string(_id) << " and my job is " << jobMap[_state.job] << std::endl;
        std::cout << "You can do my logic by adding a class ${JOBNAME} : ABotPattern" << std::endl;
        // this = BOT then this->init() then update strategy ?
    }
    else
    {
        if (_state.ressources.food < 1)
        {
            survive();
        }
        else if ((_state.state == FORKED || _state.slot > 0) && canFork)
        {
            forkNewBot();
            _idBot++;
            _state.slot--;
            canFork = false;
        }
        else if (_state.slot == 0 && canFork)
        {
            queue.push_back(std::make_pair([&]()
                                           { doAction(FORK, ""); }, "FORK"));
        }
    }
    if (timeToKnowHisIdentity == 2)
    {
        _state.job = FORKER;
    }
}
