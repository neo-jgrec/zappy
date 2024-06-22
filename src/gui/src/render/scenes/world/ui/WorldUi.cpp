/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WorldUi
*/

#include "WorldUi.hpp"
#include "../World.hpp"

static const std::vector<std::string> orientation = {
    "NORTH",
    "EAST",
    "SOUTH",
    "WEST"
};

void WorldUi::init()
{
}

bool WorldUi::update(sf::Event event, sf::RenderWindow &window)
{
    int index = 0;

    for (auto &button : _layer1) {
        if (button->update(event, window)) {
            _panelState = (panelState)index;
            return true;
        }
        index++;
    }
    if (_panelState != NONE) {
        if (_layer2["closeButton"]->update(event, window)) {
            _panelState = NONE;
            return true;
        }
    }
    if (_panelState == TRANTORIAN) {
        if (_layer2["prevButton"]->update(event, window)) {
            if (_world->getNbTrantorian() == 0)
                return false;
            _idPlayer--;
            if (_idPlayer < 0)
                _idPlayer = _world->getNbTrantorian() - 1;
        }
        if (_layer2["nextButton"]->update(event, window)) {
            if (_world->getNbTrantorian() == 0)
                return false;
            _idPlayer = (_idPlayer + 1) % _world->getNbTrantorian();
        }
    }
    if (_panelState == FLAG) {
        if (_layer2["prevButton"]->update(event, window)) {
            _idTeam--;
            if (_idTeam < 0)
                _idTeam = _world->_teams.size() - 1;
        }

        if (_layer2["nextButton"]->update(event, window)) {
            _idTeam = (_idTeam + 1) % _world->_teams.size();
        }

    }
    return false;
}

void WorldUi::update(float /*fElapsedTime*/)
{
}

void WorldUi::draw(sf::RenderWindow &window)
{
    for (auto &button : _layer1)
        button->draw(window);
    if (_panelState != NONE)
        _layer2["closeButton"]->draw(window);
    if (_panelState == TRANTORIAN)
        drawPlayerInventory(window);
    else if (_world->_selectedTile.x != -1 && _world->_selectedTile.y != -1)
        drawTileInventory(window);
    if (_panelState == TROPHY)
        drawRanking(window);
    if (_panelState == TRANTORIAN)
        drawTrantorian(window);
    if (_panelState == FLAG)
        drawTeam(window);
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

void WorldUi::drawRanking(sf::RenderWindow &window)
{
    _sprites["trophyPanel"]->draw(window);
    int index = 0;
    for (auto rank : _world->_rankings) {
        _inventoryText.setPosition(sf::Vector2f(
            _sprites["trophyPanel"]->getPosition().x + 96,
            _sprites["trophyPanel"]->getPosition().y + 32 + 40 * index
        ));
        _inventoryText.setString(rank._teamName + " : " + std::to_string(rank._score));
        window.draw(_inventoryText);
        index++;
    }
}

void WorldUi::drawTeam(sf::RenderWindow &window)
{
    _sprites["flagPanel"]->draw(window);
    _layer2["prevButton"]->draw(window);
    _layer2["nextButton"]->draw(window);

    Ranking rank;
    for (auto team: _world->_rankings) {
        if (team._teamName == _world->_teams[_idTeam]) {
            rank = team;
            break;
        }
    }

    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trophyPanel"]->getPosition().x + 96,
        _sprites["trophyPanel"]->getPosition().y + 40
    ));
    _inventoryText.setString("team " + rank._teamName);
    window.draw(_inventoryText);

    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trophyPanel"]->getPosition().x + 96,
        _sprites["trophyPanel"]->getPosition().y + 40 + 25
    ));
    _inventoryText.setString(std::to_string(rank._score) + " points");
    window.draw(_inventoryText);

    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trophyPanel"]->getPosition().x + 96,
        _sprites["trophyPanel"]->getPosition().y + 40 + 50
    ));
    _inventoryText.setString(std::to_string(rank._nbPlayer) + " trantorians");
    window.draw(_inventoryText);

}

void WorldUi::drawTrantorian(sf::RenderWindow &window)
{
    _sprites["trantorianPanel"]->draw(window);
    _layer2["prevButton"]->draw(window);
    _layer2["nextButton"]->draw(window);
    _sprites["bousolle"]->setPosition(sf::Vector2f(
        window.getSize().x - 256 / 4,
        256 / 4
    ));
    _sprites["bousolle"]->draw(window);
    if (_world->getNbTrantorian() == 0)
        return;
    auto trantorian = _world->getTrantorian(_idPlayer);
    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trantorianPanel"]->getPosition().x + + 96,
        _sprites["trantorianPanel"]->getPosition().y + 32
    ));
    if (trantorian.isDead()) {
        _inventoryText.setString("Dead");
        window.draw(_inventoryText);
        return;
    }
    _inventoryText.setString("Trantorian #" + std::to_string(trantorian._id));
    window.draw(_inventoryText);
    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trantorianPanel"]->getPosition().x + + 96,
        _sprites["trantorianPanel"]->getPosition().y + 32 + 25
    ));
    _inventoryText.setString("Level " + std::to_string(trantorian._level));
    window.draw(_inventoryText);
    _inventoryText.setPosition(sf::Vector2f(
        _sprites["trantorianPanel"]->getPosition().x + + 96,
        _sprites["trantorianPanel"]->getPosition().y + 32 + 50
    ));
    _inventoryText.setString("Facing " + orientation[trantorian._facing - 1]);
    window.draw(_inventoryText);
}

void WorldUi::drawTileInventory(sf::RenderWindow &window)
{
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
        _inventoryText.setString("Chunck inventory");
        _inventoryText.setPosition(sf::Vector2f(
            _sprites["inventory"]->getPosition().x,
            _sprites["inventory"]->getPosition().y - 64
        ));
        window.draw(_inventoryText);
}

void WorldUi::drawPlayerInventory(sf::RenderWindow &window)
{
    if (_world->getNbTrantorian() == 0)
        return;
    _sprites["inventory"]->setPosition(sf::Vector2f(
        window.getSize().x / 2,
        window.getSize().y - 32
        ));
    _sprites["inventory"]->draw(window);
    drawInventoryTile(0, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[1]));
    drawInventoryTile(1, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[2]));
    drawInventoryTile(2, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[3]));
    drawInventoryTile(3, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[4]));
    drawInventoryTile(4, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[5]));
    drawInventoryTile(5, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[6]));
    _sprites["food"]->setPosition(sf::Vector2f(
        _sprites["inventory"]->getPosition().x + 61 * 2,
        _sprites["inventory"]->getPosition().y
    ));
    _sprites["food"]->draw(window);
    drawInventoryTile(6, window, std::to_string(_world->getTrantorian(_idPlayer)._inventory[0]));
    _inventoryText.setString("Trantorian inventory");
        _inventoryText.setPosition(sf::Vector2f(
            _sprites["inventory"]->getPosition().x,
            _sprites["inventory"]->getPosition().y - 64
        ));
        window.draw(_inventoryText);
}