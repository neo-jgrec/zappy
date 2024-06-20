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
    for (auto &button : _layer1) {
        if (button->update(event, window)) {
            for (auto &button2 : _layer1) {
                if (button2 != button)
                    button2->release();
            }
            return true;
        }
    }
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
    if (_panelState != NONE)
        _panel->draw(window);
}
