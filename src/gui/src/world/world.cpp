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


    for (int i = 0; i < _size.x; i++) {
        for (int j = 0; j < _size.y; j++) {
            _sprite->_sprite.setPosition(
                i * 46 - j * 46 - _tileSize.x / 4 * 3 + _worldSize.x / 2 + _pos.x + _offset.x,
                j * 27 + i * 27 + _pos.y  + _offset.y + (int)(_chuncks[i][j]._yOffset * 80)
            );
            window.draw(_sprite->_sprite);
        }
    }
}