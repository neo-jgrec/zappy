/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AdvancedButton
*/

#ifndef ADVANCEDBUTTON_HPP_
#define ADVANCEDBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include <memory>

class AdvancedButton {
    public:
        AdvancedButton(std::string path, sf::Vector2f pos, sf::Vector2f size, float scale = 1)
        {
            _pos = pos;
            _size = size;
            _texture.loadFromFile(path);
            _sprite.setTexture(_texture);
            _sprite.setPosition(pos);
            _sprite.setScale(scale, scale);
        }
        ~AdvancedButton() {};

        bool update(sf::Event event, sf::RenderWindow &window)
        {
            if (_sprite.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                if (event.type == sf::Event::MouseButtonPressed) {
                    _state = CLICKED;
                    return true;
                }
                _state = HOVER;
            } else if (_state != CLICKED)
                _state = NORMAL;
            return false;
        }

        void draw(sf::RenderWindow &window)
        {
            _sprite.setTextureRect(sf::IntRect(_state * _size.x, 0, _size.x, _size.y));
            window.draw(_sprite);
        }

    protected:
    private:
        enum ButtonState {
            NORMAL,
            HOVER,
            CLICKED
        };
        ButtonState _state = NORMAL;
        sf::Sprite _sprite;
        sf::Texture _texture;
        sf::Vector2f _pos;
        sf::Vector2f _size;
};

#endif /* !ADVANCEDBUTTON_HPP_ */
