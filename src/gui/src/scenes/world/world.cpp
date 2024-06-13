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

    _view.setCenter(sf::Vector2f(
        10 * 46 - 10 * 46 - _tileSize.x / 4 * 3 + _tmpOffset.x + _offset.x,
                    10 * 27 + 10 * 27 + (int)(_chuncks[10][10]._yOffset * 80) - _tileSize.y + _tmpOffset.y + _offset.y
    ));
    window.setView(_view);
    for (int i = 0; i < _worldSize.x; i++) {
        for (int j = 0; j < _worldSize.y; j++) {
            _sprite->_sprite.setPosition(
                i * 46 - j * 46 - _tileSize.x / 4 * 3,
                j * 27 + i * 27 + (int)(_chuncks[i][j]._yOffset * 80)
            );
            window.draw(_sprite->_sprite);
            if (i == _hoveredTile.x && j == _hoveredTile.y) {
                _sprites["halo1"]->_sprite.setPosition(
                    i * 46 - j * 46 - _tileSize.x / 4 * 3,
                    j * 27 + i * 27 + (int)(_chuncks[i][j]._yOffset * 80) - _tileSize.y
                );
                window.draw(_sprites["halo1"]->_sprite);
            }
        }
    }
    window.setView(window.getDefaultView());
}

bool World::update(sf::Event event, sf::RenderWindow &window)
{
    if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < _gameSize.x; i++) {
            for (int j = 0; j < _gameSize.y; j++) {
                _diamond.setPosition(sf::Vector2f(
                    i * 46 - j * 46 - _tileSize.x / 4 * 3,
                    j * 27 + i * 27 + (int)(_chuncks[i][j]._yOffset * 80)
                ));
                if (_diamond.checkCollision(_zappy.getMousePos())) {
                    _hoveredTile = sf::Vector2f(i, j);
                    break;
                }
            }
        }
    }
    moveMap(event);
    return true;
}

bool World::moveMap(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            _zoom += 0.1;
        } else {
            _zoom -= 0.1;
        }
        std::cout << _zoom << std::endl;
        _view.setSize(sf::Vector2f(1920 * _zoom, 1080 * _zoom));
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = true;
            _dragStart = _zappy.getMousePos();
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = false;
            _offset += _tmpOffset;
            _tmpOffset = sf::Vector2f(0, 0);
    }
    if (_isDragging)
        _tmpOffset = -_zappy.getMousePos() + _dragStart;
    return true;
}