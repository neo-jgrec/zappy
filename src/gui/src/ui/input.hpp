/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>

#include "IButton.hpp"
#include "../sprites/sprite.hpp"

class Input : public IButton {
    public:
        Input(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font &font) {
            _text.setFont(font);
            _text.setString(text);
            _text.setPosition(pos);
            _text.setCharacterSize(24);
            _text.setFillColor(sf::Color::White);
        }
        ~Input() {}

        bool update(sf::Event event, sf::RenderWindow &window) override {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            
            return false;
        }
        void draw(sf::RenderWindow &window) override {
            if (_state == HOVER)
                _text.setFillColor(sf::Color::Red);
            else
                _text.setFillColor(sf::Color::White);
            window.draw(_text);
        }
        void setEvent(std::function<void()> event) {
            _event = event;
        }

        std::String getInput() {
            return _input;
        }

    protected:
    private:
        std:String _input;
        sf::Text _text;
        
};

#endif /* !BUTTON_HPP_ */
