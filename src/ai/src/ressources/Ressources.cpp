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

size_t Ressources::getRessource(const std::string &ressource) const
{
    auto it = ressourcesMap.find(ressource);
    if (it != ressourcesMap.end())
    {
        return *(it->second);
    }
    return 0;
}