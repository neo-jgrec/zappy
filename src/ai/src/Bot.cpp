/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Bot.cpp
*/

#include "Bot.hpp"

void Bot::init(int sockfd, const std::string &teamName)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    _sockfd = sockfd;
    _teamName = teamName;
    sendMessage(teamName);
    _behaviors.push_back(std::make_unique<Behavior>(0.4, [&]()
                                                    { survive(); }, "survive"));
    for (auto &behavior : _behaviors)
    {
        behavior->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    debugInitialisation();
    /* probabilities */
    _probabilities.push_back(std::make_unique<Probability>(5, 0.4, "food_importance"));
    _probabilities.push_back(std::make_unique<Probability>(5, 0.3, "linemate_importance"));
    debugProbabilities();
}

void Bot::updateProbabilities()
{
    // Update behaviors depending on the state of the bot
    // MACHINE LEARNING OF IA: The bot whill choose itself the numbers here
    for (auto &behavior : _behaviors)
    {
        double newProbability = behavior->probability;

        // if (state.ressources.food < getProbabilityByName("food_importance").condition) V2

        if (behavior->name == "survive")
        {
            newProbability += getProbabilityByName("food_importance").probability * std::log(1 + _state.ressources.food);
        }
        if (behavior->name == "searchLinemate")
        {
            // if (state.ressources.linemate != 1 && state.level != 3 && state.level != 7)
            // {
            newProbability += getProbabilityByName("linemate_importance").probability * std::log(1 + _state.ressources.linemate);
            // }
            // if (state.ressources.linemate != 2 && state.level != 1 && state.level != 2 && state.level != 4 && state.level != 5 &&
            //     state.level != 6 && state.level != 8)
            // {
            // newProbability = getProbabilityByName("linemate_importance").probability;
            // }
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
