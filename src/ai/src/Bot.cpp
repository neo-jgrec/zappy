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

    _behaviors.push_back(std::make_unique<Behavior>(0, [&]()
                                                    { survive(); }, "survive"));
    _behaviors.push_back(std::make_unique<Behavior>(0, [&]()
                                                    { searchLinemate(); }, "searchLinemate"));

    for (auto &behavior : _behaviors)
    {
        behavior->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    try
    {
        loadConfig("./src/ai/config/config.txt");
    }
    catch (const std::exception &e)
    {
        PRINT_ERROR(e.what());
        exit(EXIT_FAILURE); // TODO: should close server socket
    }
    debugInitialisation();
    debugTrainedVariables();
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
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["food_importance"], "food_importance"));
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["food_probability"], "food_probability"));
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["linemate_probability"], "linemate_probability"));
}

// TODO: verify it with Garance
// Update behaviors depending on the state of the bot
// MACHINE LEARNING OF IA: The bot whill choose itself the numbers here
void Bot::updateProbabilities()
{
    // double baseline_survive = 0.5;
    // double baseline_searchLinemate = 0.5;
    double baseline = 0.05;

    for (auto &behavior : _behaviors)
    {
        double newProbability = behavior->probability;

        if (behavior->name == "survive")
        {
            if (_state.ressources.food < getTrainedVariableValueByName("food_importance"))
                newProbability += getTrainedVariableValueByName("food_probability") * std::log(1 + _state.ressources.food);
            else
                newProbability = baseline;
        }
        if (behavior->name == "searchLinemate")
        {
            if (_state.level == 1 && _state.ressources.linemate != 1)
                newProbability += getTrainedVariableValueByName("linemate_probability") * std::log(1 + _state.ressources.linemate);
            else
                newProbability = baseline;
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
