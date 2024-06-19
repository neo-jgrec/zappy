/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Pattern.cpp
*/

#include "Pattern.hpp"

Pattern::Pattern(std::function<void()> act, std::string name)
{
    this->act = act;
    this->name = name;
}

Pattern::~Pattern()
{
}
