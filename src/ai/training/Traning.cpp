/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Traning.cpp
*/

#include "../Bot.hpp"

void Bot::updateProbabilities()
{
    // Update behaviors depending on the state of the bot
    // MACHINE LEARNING OF IA: The bot whill choose itself the numbers here
    for (auto &behavior : behaviors)
    {
        double newProbability = behavior->probability;

        // if (state.ressources.food < getProbabilityByName("food_importance").condition) V2
        if (behavior->name == "survive")
        {
            if (state.ressources.food < 20)
            {
                newProbability = getProbabilityByName("food_importance").probability;
            }
        }

        if (newProbability > 1)
        {
            newProbability = 1;
        }
        else if (newProbability < 0)
        {
            newProbability = 0;
        }

        behavior->probability = newProbability;
    }
    normalizeProbabilities();
}

// It redistributes the probabilities so that they sum to 1
void Bot::normalizeProbabilities()
{
    double sum = 0.0;

    for (const auto &behavior : behaviors)
    {
        sum += behavior->probability;
    }

    if (sum > 0.0)
    {
        for (auto &behavior : behaviors)
        {
            behavior->probability /= sum;
        }
    }
}

Probability &Bot::getProbabilityByName(const std::string &name)
{
    auto it = std::find_if(probabilities.begin(), probabilities.end(), [&name](const std::unique_ptr<Probability> &b)
                           { return b->name == name; });

    if (it != probabilities.end())
    {
        return **it;
    }

    throw std::runtime_error("Behavior not found");
}

// to verify: do it with condition too
void Bot::exploreProbabilities()
{
    state.exploredProbabilities.clear();

    int randomIndex = rand() % probabilities.size();
    double change = ((rand() % 100) / 100.0) * 0.2 - 0.1; // Change between -0.1 and 0.1

    probabilities[randomIndex]->probability += change;

    // Clamp the probability values between 0 and 1
    if (probabilities[randomIndex]->probability > 1)
        probabilities[randomIndex]->probability = 1;
    else if (probabilities[randomIndex]->probability < 0)
        probabilities[randomIndex]->probability = 0;

    state.exploredProbabilities.push_back(probabilities[randomIndex]->name);

    printKeyValueColored("Exploring probability", probabilities[randomIndex]->name + " with change: " + std::to_string(change));
}
