/*
** EPITECH PROJECT, 2024
** zappy/ai
** File description:
** Ressources.hpp
*/

#ifndef RESSOURCES_HPP_
#define RESSOURCES_HPP_

#include <iostream>
#include <unordered_map>

class Ressources
{
public:
    Ressources();
    ~Ressources();

    void addRessource(std::string ressource);
    void addRessourceByQuantity(std::string ressource, size_t quantity);
    size_t getRessource(const std::string &ressource) const;

    size_t food;
    size_t linemate;
    size_t deraumere;
    size_t sibur;
    size_t mendiane;
    size_t phiras;
    size_t thystame;
    size_t player;

    // void setFood(int food);
    // void setLinemate(int linemate);
    // void setDeraumere(int deraumere);
    // void setSibur(int sibur);
    // void setMendiane(int mendiane);
    // void setPhiras(int phiras);
    // void setThystame(int thystame);

    // int getFood() const;
    // int getLinemate() const;
    // int getDeraumere() const;
    // int getSibur() const;
    // int getMendiane() const;
    // int getPhiras() const;
    // int getThystame() const;
private:
    std::unordered_map<std::string, size_t *> ressourcesMap;
    //hello
    
};

#endif // RESSOURCES_HPP_
