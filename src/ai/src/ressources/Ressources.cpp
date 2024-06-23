/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Ressources.cpp
*/

#include "Ressources.hpp"

Ressources::Ressources()
{
    ressourcesMap["food"] = &food;
    ressourcesMap["linemate"] = &linemate;
    ressourcesMap["deraumere"] = &deraumere;
    ressourcesMap["sibur"] = &sibur;
    ressourcesMap["mendiane"] = &mendiane;
    ressourcesMap["phiras"] = &phiras;
    ressourcesMap["thystame"] = &thystame;
    ressourcesMap["player"] = &player;

    food = 0;
    linemate = 0;
    deraumere = 0;
    sibur = 0;
    mendiane = 0;
    phiras = 0;
    thystame = 0;
    player = 0;
}

Ressources::~Ressources()
{
}

void Ressources::addRessource(std::string ressource)
{
    auto it = ressourcesMap.find(ressource);
    if (it != ressourcesMap.end())
    {
        (*(it->second))++;
    }
}

int Ressources::getRessource(const std::string &ressource) const
{
    auto it = ressourcesMap.find(ressource);
    if (it != ressourcesMap.end())
    {
        return *(it->second);
    }
    return 0;
}

void Ressources::addRessourceByQuantity(std::string ressource, size_t quantity)
{
    if (ressourcesMap.find(ressource) != ressourcesMap.end()) {
        *(ressourcesMap[ressource]) += quantity;
    } else {
        std::cerr << "Unknown resource: " << ressource << std::endl;
    }
}

void Ressources::clear()
{
    food = 0;
    linemate = 0;
    deraumere = 0;
    sibur = 0;
    mendiane = 0;
    phiras = 0;
    thystame = 0;
    player = 0;
}

Ressources Ressources::operator+=(const Ressources &ressources)
{
    food += ressources.food;
    linemate += ressources.linemate;
    deraumere += ressources.deraumere;
    sibur += ressources.sibur;
    mendiane += ressources.mendiane;
    phiras += ressources.phiras;
    thystame += ressources.thystame;
    player += ressources.player;
    return *this;
}

