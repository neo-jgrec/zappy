/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Traning.cpp
*/

#include "../Bot.hpp"

// It redistributes the probabilities so that they sum to 1
void ABotProbabilistic::normalizeProbabilities()
{
    double sum = 0.0;

    for (const auto &behavior : _behaviors)
    {
        sum += behavior->probability;
    }

    if (sum > 0.0)
    {
        for (auto &behavior : _behaviors)
        {
            behavior->probability /= sum;
        }
    }
}

Probability &ABotProbabilistic::getProbabilityByName(const std::string &name)
{
    auto it = std::find_if(_probabilities.begin(), _probabilities.end(), [&name](const std::unique_ptr<Probability> &b)
                           { return b->name == name; });

    if (it != _probabilities.end())
    {
        return **it;
    }

    throw std::runtime_error("Behavior not found");
}

// to verify: do it with condition too
// to verify: change could  be negativ ? V2
//     double change = ((rand() % 100) / 100.0) * 0.2 - 0.1; // Change between -0.1 and 0.1
void ABotProbabilistic::exploreProbabilities()
{
    _state.exploredProbabilities.clear();

    int randomIndex = rand() % _probabilities.size();
    double change = (rand() % 100) / 100.0 * 0.1; // Change between 0 and 0.1

    _probabilities[randomIndex]->probability += change;

    // Clamp the probability values between 0 and 1
    if (_probabilities[randomIndex]->probability > 1)
        _probabilities[randomIndex]->probability = 1;

    _state.exploredProbabilities.push_back(_probabilities[randomIndex]->name);

    printKeyValueColored("Exploring probability", _probabilities[randomIndex]->name + " with change: " + std::to_string(change));
}
