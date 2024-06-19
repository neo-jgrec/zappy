/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Patterns.cpp
*/

#include "Pattern.hpp"

Pattern::Pattern(double probability, std::function<void()> act, std::string name) : probability(probability), act(act), name(name){};
Pattern::~Pattern(){};
