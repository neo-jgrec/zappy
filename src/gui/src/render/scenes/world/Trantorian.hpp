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
        Trantorian(sf::Vector2f tile, sf::Vector2f targetPos)
            : _tile(tile), _targetPos(targetPos), _pos(targetPos)
        {
            _sprites.push_back(std::make_shared<Sprite>("./assets/trantorian_spawn.png", 12, 0.1f));
            _sprites[0]->disableLooping();
            _sprites.push_back(std::make_shared<Sprite>("./assets/trantorian_run.png", 6, 0.1f));
            _sprites.push_back(std::make_shared<Sprite>("./assets/trantorian_death.png", 13, 0.1f));
            _sprites[2]->disableLooping();
        }
        ~Trantorian() {
        }

        void update(float deltaTime) {
            _pos = Lerp::lerp(_pos, _targetPos, 1.f * deltaTime);
            _sprites[_actualSprite]->setPosition(_pos);
            int ret = _sprites[_actualSprite]->update(deltaTime);
            if (ret == 1 && _actualSprite == 0) {
                _actualSprite = 1;
            }
            if (_dead == true)
                _actualSprite = 2;
        }
        void draw(sf::RenderWindow &window) {
            _sprites[_actualSprite]->draw(window);
        }
        void setTile(sf::Vector2f tile, sf::Vector2f targetPos) {
            _tile = tile;
            _targetPos = targetPos;
        }
        sf::Vector2f getTile() { return _tile; }
        void kill() { _dead = true; }

        int _id;
    protected:
    private:
        int _actualSprite = 0;
        sf::Vector2f _pos;
        std::vector<std::shared_ptr<Sprite>> _sprites;
        sf::Vector2f _tile = sf::Vector2f(0, 0);
        sf::Vector2f _targetPos = sf::Vector2f(0, 0);
        bool _dead = false;
};

#endif /* !TRANTORIAN_HPP_ */
