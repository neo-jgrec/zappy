/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#include "world.hpp"

void World::draw(sf::RenderWindow &window)
{
    int i = 0;
    int x, y;

    // _view.setCenter(sf::Vector2f(
    //     10 * 46 - 10 * 46 - _tileSize.x / 4 * 3 + _pos.x,
    //                 10 * 27 + 10 * 27 + _pos.y  + _offset.y + (int)(_chuncks[10][10]._yOffset * 80) - _tileSize.y
    // ));
    // _view.setSize(sf::Vector2f(1280 / 2 , 720 / 2));
    // _view.setCenter(sf::Vector2f(1280 / 4, 720 / 4));
    // window.setView(_view);
    for (int i = 0; i < _worldSize.x; i++) {
        for (int j = 0; j < _worldSize.y; j++) {
            _sprite->_sprite.setPosition(
                i * 46 - j * 46 - _tileSize.x / 4 * 3 + _pos.x,
                j * 27 + i * 27 + _pos.y  + _offset.y + (int)(_chuncks[i][j]._yOffset * 80)
            );
            window.draw(_sprite->_sprite);
            if (i == _hoveredTile.x && j == _hoveredTile.y) {
                _sprites["halo1"]->_sprite.setPosition(
                    i * 46 - j * 46 - _tileSize.x / 4 * 3 + _pos.x,
                    j * 27 + i * 27 + _pos.y  + _offset.y + (int)(_chuncks[i][j]._yOffset * 80) - _tileSize.y
                );
                window.draw(_sprites["halo1"]->_sprite);
            }
        }
    }
    // -> uncomment this to see the hovered tile
    // _tileShape.setPosition(
    //     _hoveredTile.x * 46 - _hoveredTile.y * 46 - _tileSize.x / 4 * 3 + _pos.x + _offset.x,
    //     _hoveredTile.y * 27 + _hoveredTile.x * 27 + _pos.y  + _offset.y + (int)(_chuncks[_hoveredTile.x][_hoveredTile.y]._yOffset * 80)
    // );
    // window.draw(_tileShape);
    // window.setView(window.getDefaultView());
}

bool World::update(sf::Event event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < _gameSize.x; i++) {
            for (int j = 0; j < _gameSize.y; j++) {
                _tileShape.setPosition(
                    i * 46 - j * 46 - _tileSize.x / 4 * 3  + _pos.x + _offset.x,
                    j * 27 + i * 27 + _pos.y  + _offset.y + (int)(_chuncks[i][j]._yOffset * 80)
                );
                if (_tileShape.getGlobalBounds().contains(_zappy.getMousePos().x, _zappy.getMousePos().y)) {
                    _hoveredTile = sf::Vector2f(i, j);
                }
            }
        }
    }
    moveMap(event);
    return true;
}

bool World::moveMap(sf::Event event)
{
    // if (event.type == sf::Event::MouseButtonPressed) {
    //     if (event.mouseButton.button == sf::Mouse::Button::Left) {
    //         _lastPos = sf::Mouse::getPosition();
    //     }
    // }
    // if (event.type == sf::Event::MouseButtonPressed) {
    //     if (event.mouseButton.button == sf::Mouse::Button::Left) {
    //         _lastPos = sf::Mouse::getPosition();
    //     }
    // }
    return true;
}