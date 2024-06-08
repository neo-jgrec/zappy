/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sprite
*/

#ifndef SPRITE_HPP_
#define SPRITE_HPP_

#include <SFML/Graphics.hpp>

class Sprite {
    public:
        Sprite(const std::string &path)
        {
            if (!_texture.loadFromFile(path))
                throw std::runtime_error("Cannot load texture");
            _sprite.setTexture(_texture);
        }
        ~Sprite() {}

        void draw(sf::RenderWindow &window) { window.draw(_sprite); }

        sf::Texture _texture;
        sf::Sprite _sprite;
    private:
};

#endif /* !SPRITE_HPP_ */
