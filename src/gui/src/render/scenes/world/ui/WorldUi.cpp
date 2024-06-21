/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WorldUi
*/

#include "WorldUi.hpp"
#include "../World.hpp"

void WorldUi::init()
{
}

bool WorldUi::update(sf::Event event, sf::RenderWindow &window)
{
    int index = 0;

    for (auto &button : _layer1) {
        if (button->update(event, window)) {
            for (auto &button2 : _layer1) {
                if (button2 != button)
                    button2->release();
            }
            _panelState = (panelState)index;
            return true;
        }
        index++;
    }
    if (_panelState != NONE) {
        if (_layer2["closeButton"]->update(event, window)) {
            _panelState = NONE;
            for (auto &button : _layer1) {
                button->release();
            }
            _layer2["closeButton"]->release();
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
    if (_panelState != NONE) {
        _panel->draw(window);
        _layer2["closeButton"]->draw(window);
    }
    if (_world->_selectedTile.x != -1 && _world->_selectedTile.y != -1) {
        _sprites["inventory"]->setPosition(sf::Vector2f(
            window.getSize().x / 2,
            window.getSize().y - 32
            ));
        _sprites["inventory"]->draw(window);
        drawInventoryTile(0, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._linemate));
        drawInventoryTile(1, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._deraumere));
        drawInventoryTile(2, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._sibur));
        drawInventoryTile(3, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._mendiane));
        drawInventoryTile(4, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._phiras));
        drawInventoryTile(5, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._thystame));
        _sprites["food"]->setPosition(sf::Vector2f(
            _sprites["inventory"]->getPosition().x + 61 * 2,
            _sprites["inventory"]->getPosition().y
        ));
        _sprites["food"]->draw(window);
        _sprites["trantorian"]->setPosition(sf::Vector2f(
            _sprites["inventory"]->getPosition().x + 61 * 3,
            _sprites["inventory"]->getPosition().y + 10
        ));
        _sprites["trantorian"]->draw(window);
        drawInventoryTile(6, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._food));
        drawInventoryTile(7, window, std::to_string(_world->_chuncks[_world->_selectedTile.x][_world->_selectedTile.y]._nbTrantorians));
    }
    if (_panelState == TROPHY) {
        _sprites["trophyPanel"]->draw(window);
    }
}

void WorldUi::drawInventoryTile(int nb, sf::RenderWindow &window, std::string name)
{

    _inventoryText.setPosition(sf::Vector2f(
        _sprites["inventory"]->getPosition().x - 64 * 4 + 17 + 61 * nb,
        _sprites["inventory"]->getPosition().y - 5
    ));
    _inventoryText.setString(name);
    window.draw(_inventoryText);
}