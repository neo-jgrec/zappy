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
    _message._content = "";
    static bool _canAct = true;

    if (!responseCopy.empty() && responseCopy.back() == '\n')
    {
        responseCopy.pop_back();
    }
    printKeyValueColored("Bot listens", responseCopy);
    // TODO: it is a action response, _canAct == true
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
    updateProbabilities();

    if (_canAct)
    {
        printColor("========== [Bot Run] ==========\n", BLUE);
        printKeyValueColored("Iteration", std::to_string(_iteration));
        if (_state.state != LISTENING)
        {
            if (queue.empty())
                updateStrategy(); // -> fait l'action la plus rentable
            if (!queue.empty() && _canAct)
            {
                queue.front().first();
                _canAct = false;
                queue.erase(queue.begin());
            }
        }
        _iteration++;
        printColor("========== [!Bot Run] ==========\n", BLUE);
        if (_iteration % 20 == 0) // TODO: make it when flag --save-data is entered
        {
            saveData("./src/ai/dataSaved/behaviors.txt");
        }
    }
    if (_iteration == 200 || (responseCopy.find("dead") != std::string::npos))
    {
        debugState();
        saveData("./src/ai/dataSaved/behaviors.txt");
        exit(0);
    }
}

void ABotProbabilistic::updateStrategy()
{
    PatternProbabilistic *bestPattern = nullptr;

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
