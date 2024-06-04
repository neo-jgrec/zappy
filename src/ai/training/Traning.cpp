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

        if (state.ressources.food < 5)
        {
            if (behavior->name == "take_food")
            {
                newProbability += 0.1;
            }
        }

        if (state.level > 1)
        {
            if (behavior->name == "forward")
            {
                newProbability += 0.05;
            }
        }

        if (state.ressources.linemate > 2) // && !state.environment.contains("linemate")
        {
            if (behavior->name == "look")
            {
                newProbability -= 0.05; // decrease the probability of looking if we have enough linemate
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
