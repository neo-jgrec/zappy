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
    std::cout << "🍴✅ Forker initialized" << std::endl;
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
        // TODO: use cpp function
        //  without term
        //   execl("./zappy_ai", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        // with term that close
        // execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "./zappy_ai", "-p", std::to_string(_port).c_str(), "-n", _teamName.c_str(), "-h", _host.c_str(), nullptr);

        //  with term that stay open
        execl("/usr/bin/gnome-terminal", "/usr/bin/gnome-terminal", "--", "bash", "-c",
              ("trap 'echo \"[DEBUG]\"; kill -INT $$' SIGINT; ./zappy_ai -p " + std::to_string(_port) + " -n " + _teamName + " -h " + _host + "; exec bash").c_str(), nullptr);

        std::cerr << "execl failed" << std::endl;
        while (1)
            ;
    }
    else
    {
        std::string msg = "you_are_bot=" + std::to_string(_idBot) + "your_job=" + jobMap[SIMPLE_BOT] + "currentMessageId=" + std::to_string(_currentMessageId);
        // sleep(1);
        addBroadcastAction(msg);

        wait(nullptr);
    }
}

void Forker::updateStrategy()
{
    static unsigned int limitFork = 2; // TODO: it is to debug
    static bool verifySlot = true;

    std::cout << "🍴 Forker updateStrategy" << std::endl;
    if (verifySlot)
    {
        _state.slot = 0;
        queue.push_back(std::make_pair([&]()
                                       { doAction(CONNECT_NBR, ""); }, "CONNECT_NBR"));
        verifySlot = false;
    }
    else if (handleSurvive())
        return;
    else if ((_state.state == FORKED || _state.slot > 0) && limitFork > 0)
    {
        forkNewBot();
        // TODO: try to put a sleep because server doesn't handle multiple fork in chain sleep(2);
        _idBot++;
        _state.slot--;
        limitFork--;
    }
    else if (_state.slot == 0 && limitFork > 0)
    {
        queue.push_back(std::make_pair([&]()
                                       { doAction(FORK, ""); }, "FORK"));
    }
}

bool Forker::handleSurvive()
{
    static int searchFood = 0;
    const int limitFood = 50;

    if (_iteration % 40 == 0)
    {
        _state.state = STANDARD;
        queue.push_back({[&]()
                         { doAction(INVENTORY, ""); }, "INVENTORY"});
        return true;
    }

    if (_state.ressources.food < limitFood)
    {
        // TODO: we want differant searchFood for each level ?
        searchFood = 250;
    }
    if (searchFood > 0)
    {
        if (searchFood == 1)
            queue.push_back({[&]()
                             { doAction(INVENTORY, ""); }, "INVENTORY"});
        else
            survive();
        _state.state = STANDARD;
        _state.pattern = "survive";
        searchFood--;
        return true;
    }
    return false;
}