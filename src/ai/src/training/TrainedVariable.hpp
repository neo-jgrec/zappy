/*
** EPITECH PROJECT, 2024
** zappy/ai/traning
** File description:
** TrainedVariables.hpp
*/

#ifndef TRAINEDVARIABLES_HPP_
#define TRAINEDVARIABLES_HPP_

#include <iostream>

class TrainedVariable
{
public:
    TrainedVariable(double valueParam, const std::string &nameParam);
    ~TrainedVariable();

    double value; // TODO: should be in private
    std::string name;
};
#endif // TRAINEDVARIABLES_HPP_
