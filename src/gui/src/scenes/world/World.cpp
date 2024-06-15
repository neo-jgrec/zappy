/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/


#include "World.hpp"
#include "../../utils/PerlinNoise.hpp"

#include <iostream>

void World::draw(sf::RenderWindow &window)
{
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
            if (i == _hoveredTile.x && j == _hoveredTile.y && !_isDragging) {
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

bool World::update(sf::Event event, [[maybe_unused]] sf::RenderWindow &window)
{
    _mousePos = _zappy.getMousePos();
    _mousePos = sf::Vector2f(
        (_mousePos.x * _zoom + _view.getCenter().x - _view.getSize().x / 2),
        (_mousePos.y * _zoom + _view.getCenter().y - _view.getSize().y / 2)
    );
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _zappy._upperState = GameState::MENU;
    if (event.type == sf::Event::MouseMoved) {
        for (int i = 0; i < _gameSize.x; i++) {
            for (int j = 0; j < _gameSize.y; j++) {
                _diamond.setPosition(sf::Vector2f(
                    i * 46 - j * 46 - _tileSize.x / 4 * 3,
                    j * 27 + i * 27 + (int)(_chuncks[i][j]._yOffset * 80)
                ));
                if (_diamond.checkCollision(_mousePos)) {
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
        _tmpOffset = - _zappy.getMousePos() + _dragStart;
    return true;
}

void World::init() {
    PerlinNoise noise;

    for (int i = 0; i < _worldSize.x; i++) {
        std::vector<Chunck> chuncks;
        for (int j = 0; j < _worldSize.y; j++) {
            Chunck chunck;
            chunck._pos = sf::Vector2i(i, j);
            chunck._yOffset = noise.noise(i * 0.1, j * 0.1);
            chuncks.push_back(chunck);
        }
        _chuncks.push_back(chuncks);
    }
    _sprite = std::make_shared<Sprite>("./assets/grass.png");
    _tileSize = sf::Vector2f(
        _sprite->_sprite.getTexture()->getSize().x,
        _sprite->_sprite.getTexture()->getSize().y
    );
    _diamond = Diamond(_tileSize);
    // sf::Vector2f _viewSize = sf::Vector2f((_worldSize.x * _tileSize.x) / 2 + (_worldSize.y * _tileSize.x) / 2,
    //     (_worldSize.x * _tileSize.y) / 2 + (_worldSize.y * _tileSize.y) / 2);
    _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
    _view.setSize(sf::Vector2f(1920 , 1080));
}
