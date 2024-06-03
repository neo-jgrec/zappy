/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Behaviors.cpp
*/

#include "Behavior.hpp"

Behavior::Behavior(int probability, std::function<void()> act, std::string name) : probability(probability), act(act), name(name){};
Behavior::~Behavior(){};
