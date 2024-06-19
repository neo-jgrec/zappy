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

    for (const auto &pattern : _patterns)
    {
        sum += pattern->probability;
    }

    if (sum > 0.0)
    {
        for (auto &pattern : _patterns)
        {
            pattern->probability /= sum;
        }
    }
}

const double &ABotProbabilistic::getTrainedVariableValueByName(const std::string &name) const
{
    auto it = std::find_if(_trainedVariables.begin(), _trainedVariables.end(), [&name](const std::unique_ptr<TrainedVariable> &b)
                           { return b->name == name; });

    if (it != _trainedVariables.end())
    {
        return it->get()->value;
    }

    throw std::runtime_error("pattern not found");
}
