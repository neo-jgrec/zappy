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
    try
    {
        loadConfig("./src/ai/config.txt");
    }
    catch (const std::exception &e)
    {
        PRINT_ERROR(e.what());
        exit(EXIT_FAILURE); // TODO: should close server socket
    }
    debugInitialisation();
    debugProbabilities();
}

void Bot::loadConfig(const std::string &filename)
{
    std::ifstream configStream(filename);

    if (!configStream.is_open())
    {
        throw std::runtime_error("Unable to open config file: " + filename);
        return;
    }

    std::string line;
    std::unordered_map<std::string, double> configValues;

    while (std::getline(configStream, line))
    {
        std::istringstream iss(line);
        std::string key;
        double value;

        if (std::getline(iss, key, '=') && iss >> value)
        {
            configValues[key] = value;
        }
    }
    _probabilities.push_back(std::make_unique<Probability>(configValues["food_importance.condition"], configValues["food_importance.probability"], "food_importance"));
    _probabilities.push_back(std::make_unique<Probability>(configValues["linemate_importance.condition"], configValues["linemate_importance.probability"], "linemate_importance"));
}

void Bot::updateProbabilities()
{
    // Update behaviors depending on the state of the bot
    // MACHINE LEARNING OF IA: The bot whill choose itself the numbers here
    for (auto &behavior : _behaviors)
    {
        double newProbability = behavior->probability;

        if (behavior->name == "survive")
        {
            if (_state.ressources.food < getProbabilityByName("food_importance").condition)
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
