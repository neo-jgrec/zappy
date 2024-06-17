/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Trantorien
*/

#ifndef TRANTORIAN_HPP_
#define TRANTORIAN_HPP_

#include "../../sprites/Sprite.hpp"

class Trantorian {
    public:
        Trantorian(Sprite sprite)
            : _sprite(sprite)
        {
        }
        ~Trantorian() {
        }

        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        void setSize(sf::Vector2f size) { _sprite.setSize(size); }

        void update() { _sprite.update(); }
        void draw(sf::RenderWindow &window) { _sprite.draw(window); }

        sf::Vector2f _tile;
    protected:
    private:
        Sprite _sprite;
        sf::Vector2f _offSet;
};

#endif /* !TRANTORIAN_HPP_ */
