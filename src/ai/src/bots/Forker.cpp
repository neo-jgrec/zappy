/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Forker.cpp
*/

#include "Forker.hpp"
#include "SimpleBot.hpp"

void Forker::initChild()
{
    doAction(INVENTORY, "");
    std::cout << "🍴 Forker initialized" << std::endl;
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
        // without term
        //  execl("./zappy_ai", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);
        // with term that close
        //  execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);
        //  with term that stay open
        execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "bash", "-c",
              ("trap 'echo \"[DEBUG]\"; kill -INT $$' SIGINT; ./zappy_ai -p " + std::to_string(_port) + " -n " + _teamName + " -h " + _host + "; exec bash").c_str(), nullptr);

        std::cerr << "execl failed" << std::endl;
        while (1)
            ;
    }
    else
    {
        _message.format("you_are_bot=" + std::to_string(_idBot) + "your_job=" + jobMap[SIMPLE_BOT] + "currentMessageId=" + std::to_string(_currentMessageId));
        queue.push_back(std::make_pair([&]()
                                       { doAction(BROADCAST, _message._content); }, "FORK"));

        wait(nullptr);
    }
}

void Forker::updateStrategy()
{
    static bool canFork = true; // TODO: it is to debug
    static bool verifySlot = true;

    std::cout << "🍴 Forker updateStrategy" << std::endl;
    if (verifySlot)
    {
        _state.slot = 0;
        queue.push_back(std::make_pair([&]()
                                       { doAction(CONNECT_NBR, ""); }, "CONNECT_NBR"));
        verifySlot = false;
    }
    else if (_state.ressources.food < 5)
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
