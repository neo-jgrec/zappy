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
#include <iostream>

class Trantorian {
    public:
        Trantorian(Sprite sprite, Sprite trantorian_run, sf::Vector2f tile, sf::Vector2f targetPos)
            : _sprite(sprite), _tile(tile), _trantorian_run(trantorian_run)
        {
            _targetPos = _targetPos;
            _sprite.setPosition(_targetPos);
        }
        ~Trantorian() {
        }

        void update(float deltaTime) {
            _sprite.setPosition(Lerp::lerp(_sprite.getPosition(), _targetPos, 0.5f));
            // _trantorian_run.update(deltaTime);
        }
        void draw(sf::RenderWindow &window) {
            // if (_sprite.getPosition() != _targetPos) {
                _trantorian_run.setPosition(_sprite.getPosition());
                _trantorian_run.draw(window);
            // } else {
                // _sprite.draw(window);
            // }
        }
        void setTile(sf::Vector2f tile, sf::Vector2f targetPos) {
            _tile = tile;
            _targetPos = targetPos;
            // if (sqrt(pow(_sprite.getPosition().x - _targetPos.x, 2) + pow(_sprite.getPosition().y - _targetPos.y, 2)) > 10) {
            //     _sprite.setPosition(_targetPos);
            // }
        }
        sf::Vector2f getTile() { return _tile; }

        int _id;
    protected:
    private:
        Sprite _sprite;
        Sprite _trantorian_run;
        sf::Vector2f _tile = sf::Vector2f(0, 0);
        sf::Vector2f _targetPos = sf::Vector2f(0, 0);
};

#endif /* !TRANTORIAN_HPP_ */
