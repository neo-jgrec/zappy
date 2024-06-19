/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** PatternProbabilistics.cpp
*/

#include "PatternProbabilistic.hpp"

PatternProbabilistic::PatternProbabilistic(double probability, std::function<void()> act, std::string name) : probability(probability), act(act), name(name){};
PatternProbabilistic::~PatternProbabilistic(){};
