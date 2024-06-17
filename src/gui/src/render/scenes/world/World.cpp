/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/


#include "World.hpp"
#include "../../core/Core.hpp"

#include <iostream>

void World::init()
{
    while (_core->_data.getMap().getSize()[0] == 0) {
        _core->_parser.updateData(_core->_data, _core->_server);
        std::cout << "Waiting for map size" << std::endl;
    }
    _worldSize = sf::Vector2f(
        _core->_data.getMap().getSize()[0],
        _core->_data.getMap().getSize()[1]
    );
    std::cout << "World size: " << _worldSize.x << "x" << _worldSize.y << std::endl;
    PerlinNoise noise;

    for (int i = 0; i < _worldSize.x; i++) {
        std::vector<Chunck> chuncks;
        for (int j = 0; j < _worldSize.y; j++) {
            Chunck chunck;
            chunck._pos = sf::Vector2f(
                i * 46 - j * 46 - TILE_SIZE_X / 4 * 3,
                j * 27 + i * 27
            );
            chunck._yOffset = noise.noise(i * 0.1, j * 0.1) * 80;
            chuncks.push_back(chunck);
        }
        _chuncks.push_back(chuncks);
    }
    _mapDiamond = Diamond(sf::Vector2f(TILE_SIZE_X * _worldSize.x - TILE_SIZE_X * 2 , TILE_SIZE_Y * _worldSize.y));
    _mapDiamond.setPosition(sf::Vector2f(- TILE_SIZE_X * _worldSize.x / 2, 0));

    _pos = sf::Vector2f(
        (int)(_worldSize.x / 2) * TILE_SIZE_MX- (int)(_worldSize.x / 2) * TILE_SIZE_MX - TILE_SIZE_MY,
        (int)(_worldSize.y / 2) * TILE_SIZE_MY + (int)(_worldSize.y / 2) * TILE_SIZE_MY - TILE_SIZE_Y
    );
}

bool World::update(sf::Event event, [[maybe_unused]] sf::RenderWindow &window)
{
    updateTrantorians();
    _mousePos = _core->getMousePos();
    _mousePos = sf::Vector2f(
        (_mousePos.x * _zoom + _view.getCenter().x - _view.getSize().x / 2),
        (_mousePos.y * _zoom + _view.getCenter().y - _view.getSize().y / 2)
    );
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _core->_upperState = GameState::MENU;
    if (event.type == sf::Event::MouseMoved ||
        event.type == sf::Event::MouseButtonPressed) {
        for (int i = 0; i < _worldSize.x; i++) {
            for (int j = 0; j < _worldSize.y; j++) {
                _diamond.setPosition(sf::Vector2f(
                    _chuncks[i][j]._pos.x,
                    _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
                ));
                if (_diamond.checkCollision(_mousePos)) {
                    _hoveredTile = sf::Vector2f(i, j);
                    if (event.mouseButton.button == sf::Mouse::Button::Left)
                        _selectedTile = sf::Vector2f(i, j);
                    break;
                }

            }
        }
    }
    moveMap(event);
    return true;
}

void World::draw(sf::RenderWindow &window)
{
    _view.setCenter(sf::Vector2f(
        _pos.x + _tmpOffset.x + _offset.x,
        _pos.y + _tmpOffset.y + _offset.y
    ));
    window.setView(_view);
    for (int i = 0; i < _worldSize.x; i++) {
        for (int j = 0; j < _worldSize.y; j++) {
            drawChunck(window, i, j);
        }
    }
    // _mapDiamond.draw(window);
    window.setView(window.getDefaultView());
}

void World::drawChunck(sf::RenderWindow &window, int i, int j)
{
    _sprite->_sprite.setPosition(
                _chuncks[i][j]._pos.x,
                _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
            );
    window.draw(_sprite->_sprite);
    if (i == _hoveredTile.x && j == _hoveredTile.y && !_isDragging) {
        _sprites["hover1"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset
        );
        window.draw(_sprites["hover1"]->_sprite);
    }
    for (auto &trantorian : _trantorians) {
        if (trantorian.getTile().x == i && trantorian.getTile().y == j) {
            trantorian.setPosition(sf::Vector2f(
                _chuncks[i][j]._pos.x,
                _chuncks[i][j]._pos.y
            ));
            trantorian.draw(window);
        }
    }
    if (_selectedTile.x == i && _selectedTile.y == j) {
        _sprites["halo1"]->_sprite.setPosition(
            _chuncks[i][j]._pos.x,
            _chuncks[i][j]._pos.y + _chuncks[i][j]._yOffset - TILE_SIZE_Y
        );
        window.draw(_sprites["halo1"]->_sprite);
    }
}

bool World::moveMap(sf::Event event)
{
    if (event.type == sf::Event::MouseWheelScrolled) {
        if (event.mouseWheelScroll.delta > 0) {
            _zoom += 0.1;
        } else {
            _zoom -= 0.1;
        }
        if (_zoom < 0.5f)
            _zoom = 0.5f;
        if (_zoom > 2)
            _zoom = 2;
        _view.setSize(sf::Vector2f(1920 * _zoom, 1080 * _zoom));
    }
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = true;
            _dragStart = _core->getMousePos();
    }
    if (event.type == sf::Event::MouseButtonReleased &&
        event.mouseButton.button == sf::Mouse::Button::Left) {
            _isDragging = false;
            _offset += _tmpOffset;
            _tmpOffset = sf::Vector2f(0, 0);
    }
    if (_isDragging) {
        if (_core->getMousePos().x < 0 || _core->getMousePos().x > 1920 ||
            _core->getMousePos().y < 0 || _core->getMousePos().y > 1080) {
                _isDragging = false;
                _offset += _tmpOffset;
                _tmpOffset = sf::Vector2f(0, 0);
                return true;
            }
        _tmpOffset = - _core->getMousePos() + _dragStart;
    }
    return true;
}

void World::updateTrantorians()
{
    std::map<int, Player> players;
    bool exisitingPlayers = false;

    players = _core->_data.getPlayers();
    for (auto &player : players) {
        player.second.getNextEvent();

        exisitingPlayers = false;
                // std::cout << "Player " << player.first << " is at " << player.second.getPosition()[0] << "x" << player.second.getPosition()[1] << std::endl;
        for (auto &trantorian : _trantorians) {
            if (trantorian._id == player.first) {
                exisitingPlayers = true;
                trantorian.setTile(sf::Vector2f(player.second.getPosition()[0], player.second.getPosition()[1]));
                // std::cout << "Player " << player.first << " is at " << player.second.getPosition()[0] << "x" << player.second.getPosition()[1] << std::endl;
                break;
            }
        }
        if (!exisitingPlayers) {
            Trantorian trantorian(*_sprites["trantorian"], sf::Vector2f(player.second.getPosition()[0], player.second.getPosition()[1]));
            trantorian._id = player.first;
            _trantorians.push_back(trantorian);
        }

    }
}
