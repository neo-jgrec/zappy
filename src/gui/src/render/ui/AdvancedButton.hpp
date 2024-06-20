/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** AdvancedButton
*/

#ifndef ADVANCEDBUTTON_HPP_
#define ADVANCEDBUTTON_HPP_

#include <SFML/Graphics.hpp>
#include "../sprites/Sprite.hpp"
#include <memory>

class AdvancedButton {
    public:
        AdvancedButton(sf::Vector2f pos, sf::Vector2f size, std::shared_ptr<Sprite> sprite)
            : _pos(pos), _size(size), _sprite(sprite)
        {
            _pos = pos;
            _size = size;
            _sprite->setPosition(pos);
            _sprite->setSize(size);
        }
        ~AdvancedButton() {};

        bool update(sf::Event event, sf::RenderWindow &window)
        {
            if (_sprite->mouseOver(window) &&
                event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                    _sprite->setFrame(1);
                    return true;
            }
            _sprite->setFrame(0);
            return false;
        }

        void draw(sf::RenderWindow &window)
        {
            _sprite->draw(window);
        }

    protected:
    private:
        sf::Vector2f _pos;
        sf::Vector2f _size;
        std::shared_ptr<Sprite> _sprite;
};

#endif /* !ADVANCEDBUTTON_HPP_ */
