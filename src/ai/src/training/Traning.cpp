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
