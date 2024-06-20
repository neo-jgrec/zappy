/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WorldUi
*/

#include "WorldUi.hpp"

void WorldUi::init()
{
}

bool WorldUi::update(sf::Event event, sf::RenderWindow &window)
{
    return false;
}

void WorldUi::update(float fElapsedTime)
{
}

void WorldUi::draw(sf::RenderWindow &window)
{
    for (auto &button : _layer1) {
        button->draw(window);
    }
}
