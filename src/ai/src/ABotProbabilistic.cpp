/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** ABot.cpp
*/

#include "ABotProbabilistic.hpp"

ABotProbabilistic::ABotProbabilistic()
{
}

ABotProbabilistic::~ABotProbabilistic()
{
}

// if (_doNothing)
// {
//     _patterns.erase(_patterns.begin());
//     _patterns.push_back(std::make_unique<Behavior>(0.4, [&]()
//                                                     { trapMessage(); }, "trap Message"));
//     _doNothing = false;
// }
void ABotProbabilistic::run(const std::string &response)
{
    std::string responseCopy = response;

    printColor("========== [Bot Run] ==========\n", BLUE);
    printKeyValueColored("Iteration", std::to_string(_iteration));
    if (!responseCopy.empty() && responseCopy.back() == '\n')
    {
        responseCopy.pop_back();
    }
    printKeyValueColored("Bot listens", responseCopy);
    //if (responseCopy.find("message") != std::string::npos)
    //    _doNothing = true;
    listen(responseCopy);
    if (_state.lastAction.action != LISTENING)
    {
        updateProbabilities();
        if (queue.empty())
            act(); // -> fait l'action la plus rentable
        if (!queue.empty())
        {
            queue.front().first();
            queue.erase(queue.begin());
        }
    }
    _iteration++;
    printColor("========== [!Bot Run] ==========\n", BLUE);
    if (_iteration % 20 == 0) // TODO: make it when flag --save-data is entered
    {
        std::cout << "store data\n";
        saveData("./src/ai/dataSaved/behaviors.txt");
    }
    if (_iteration == 200)
    {
        debugState();
        saveData("./src/ai/dataSaved/behaviors.txt");
        exit(0);
    }
}

void ABotProbabilistic::listen(const std::string &response)
{
    if (_state.lastAction.action == LOOK)
        listenLookResponse(response);
    else if (_state.lastAction.action == TAKE)
        listenTakeResponse(response);
    else if (_state.lastAction.action == INCANTATION)
        listenIncantationResponse(response);
    else if (_state.lastAction.action == LISTENING)
        listenIncantationReturnResponse(response);
    if (response.find("message") != std::string::npos)
    {
        listenBroadcastResponse(response);
    }
}

void ABotProbabilistic::act()
{
    Pattern *bestPattern = nullptr;

    double maxProbability = -1;

    if (!_patterns.empty())
    {
        maxProbability = _patterns[0]->probability;
        bestPattern = _patterns[0].get();
    }
    for (auto &behavior : _patterns)
    {
        if (behavior->probability > maxProbability)
        {
            maxProbability = behavior->probability;
            bestPattern = behavior.get();
        }
    }
    printColor("Pattern choosen: " + bestPattern->name + "\n", BOLD);
    if (bestPattern)
    {
        bestPattern->act();
        bestPattern->count++;
    }
}

void ABotProbabilistic::saveData(const std::string &filename)
{
    std::ofstream out(filename, std::ios_base::app);

    out << "iteration:" << _iteration << "\n";
    for (const auto &pattern : _patterns)
    {
        out << pattern->name << ":" << pattern->count << "\n";
    }
    out << "\n";
}
