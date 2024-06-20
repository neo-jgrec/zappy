/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** BotProbabilistic.cpp
*/

#include "BotProbabilistic.hpp"

void BotProbabilistic::initChild()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    // if (arg)
    // {
    //     _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                                   { joinGroup(); }, "joinGroup"));
    // }
    // else
    // {
    //     _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                                   { group(); }, "group"));
    // }

    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { survive(); }, "survive"));
    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { searchLinemate(); }, "searchLinemate"));
    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { incantation({"linemate"}); }, "incantationLvl1"));
    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { incantation({"linemate", "deraumere", "sibur"}); }, "incantationLvl2"));
    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { searchDeraumere(); }, "searchDeraumere"));
    // _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
    //                                               { searchSibur(); }, "searchSibur"));
    _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
                                                               { group(); }, "group"));
    _patterns.push_back(std::make_unique<PatternProbabilistic>(0, [&]()
                                                               { joinGroup(); }, "joinGroup"));

    for (auto &pattern : _patterns)
    {
        pattern->probability = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    }
    try
    {
        loadConfig("./src/ai/config/config.txt");
        // loadConfig("./src/ai/config/config_trained.txt");
    }
    catch (const std::exception &e)
    {
        PRINT_ERROR(e.what());
        exit(EXIT_FAILURE); // TODO: should close server socket
    }
    debugInitialisation();
    debugTrainedVariables();
}

void BotProbabilistic::loadConfig(const std::string &filename)
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
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["linemate_probability_2"], "linemate_probability_2"));
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["incantation_probability"], "incantation_probability"));
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["deraumere_probability"], "deraumere_probability"));
    _trainedVariables.push_back(std::make_unique<TrainedVariable>(configValues["sibur_probability"], "sibur_probability"));
}

// TODO: verify it with Garance
// Update patterns depending on the state of the bot
// MACHINE LEARNING OF IA: The bot whill choose itself the numbers here
void BotProbabilistic::updateProbabilities()
{
    // double baseline_survive = 0.5;
    // double baseline_searchLinemate = 0.5;
    double baseline = 0.05;

    for (auto &pattern : _patterns)
    {
        double newProbability = pattern->probability;

        if (pattern->name == "survive")
        {
            if (_state.ressources.food < 10)
                newProbability = getTrainedVariableValueByName("food_probability") * std::log(1 + _state.ressources.food);
            else
                newProbability = baseline;
        }
        else if (pattern->name == "searchLinemate")
        {
            if (_state.level == 1 && _state.ressources.linemate != 1)
                newProbability = getTrainedVariableValueByName("linemate_probability") * std::log(1 + _state.ressources.linemate);
            else if (_state.level == 2 && _state.ressources.linemate != 1)
                newProbability = getTrainedVariableValueByName("linemate_probability_2") * std::log(1 + _state.ressources.linemate);
            else
                newProbability = baseline;
        }
        else if (pattern->name == "searchDeraumere")
        {
            if (_state.level == 2 && _state.ressources.deraumere != 1)
                newProbability = getTrainedVariableValueByName("deraumere_probability") * std::log(1 + _state.ressources.deraumere);
            else
                newProbability = baseline;
        }
        else if (pattern->name == "searchSibur")
        {
            if (_state.level == 2 && _state.ressources.sibur != 1)
                newProbability = getTrainedVariableValueByName("sibur_probability") * std::log(1 + _state.ressources.sibur);
            else
                newProbability = baseline;
        }
        else if (pattern->name == "incantationLvl1")
        {
            if (_state.ressources.linemate == 1 && _state.level == 1)
                newProbability = getTrainedVariableValueByName("incantation_probability");
            else
                newProbability = baseline;
        }
        else if (pattern->name == "incantationLvl2")
        {
            if (_state.ressources.linemate == 1 && _state.ressources.deraumere == 1 && _state.ressources.sibur == 1 && _state.level == 2 && _allyMessage._content == "group_joined")
                newProbability = getTrainedVariableValueByName("incantation_probability");
            else
                newProbability = baseline;
        }
        else if (pattern->name == "joinGroup")
        {
            if (_allyMessage._content.find("group") != std::string::npos)
                newProbability = 1; // TODO: make trained_variables
            else
                newProbability = baseline;
        }
        else if (pattern->name == "group")
        {
            // TODO: get state of all bots
            if (_state.ressources.linemate == 1 && _state.ressources.deraumere == 1 && _state.ressources.sibur == 1)
                newProbability = 1; // TODO: make trained_variables
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

        pattern->probability = newProbability;
    }
    normalizeProbabilities();
}