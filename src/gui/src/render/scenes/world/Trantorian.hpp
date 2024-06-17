/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Trantorien
*/

#ifndef TRANTORIAN_HPP_
#define TRANTORIAN_HPP_

#include "../../sprites/Sprite.hpp"
#include "../../core/Setting.hpp"
#include "../../../utils/Lerp.hpp"

class Trantorian {
    public:
        Trantorian(Sprite sprite, sf::Vector2f tile)
            : _sprite(sprite), _tile(tile)
        {
            // _sprite.setSize(sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y));
            _sprite.setPosition(sf::Vector2f(tile.x * TILE_SIZE_X, tile.y * TILE_SIZE_Y));
            _targetPos = sf::Vector2f(tile.x * TILE_SIZE_X, tile.y * TILE_SIZE_Y);
        }
        ~Trantorian() {
        }

        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        void setSize(sf::Vector2f size) { _sprite.setSize(size); }

        void update() {
            _sprite.setPosition(Lerp::lerp(_sprite.getPosition(), _targetPos, 0.1f));
            _sprite.update();
        }
        void draw(sf::RenderWindow &window) {
            _sprite.draw(window);
        }
        void setTile(sf::Vector2f tile) {
            _tile = tile;
            _targetPos = sf::Vector2f(tile.x * TILE_SIZE_X, tile.y * TILE_SIZE_Y);
        }
        sf::Vector2f getTile() { return _tile; }

        int _id;
    protected:
    private:
        Sprite _sprite;
        sf::Vector2f _tile = sf::Vector2f(0, 0);
        sf::Vector2f _targetPos = sf::Vector2f(0, 0);
};

#endif /* !TRANTORIAN_HPP_ */
