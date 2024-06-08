/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <SFML/Graphics.hpp>

#include "../sprites/sprite.hpp"

enum ButtonState {
    IDLE,
    HOVER,
    CLICKED,
};

class Button {
    public:
        Button(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font &font) {
            _text.setFont(font);
            _text.setString(text);
            _text.setPosition(pos);
            _text.setCharacterSize(24);
            _text.setFillColor(sf::Color::White);
        }
        ~Button() {}

        bool update(sf::Event event, sf::RenderWindow &window) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (_text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (event.type == sf::Event::MouseButtonPressed)
                    _state = CLICKED;
                else if (event.type == sf::Event::MouseButtonReleased) {
                    if (_state == CLICKED) {
                        try {
                            _event();
                        } catch (const std::bad_function_call &e) {
                            std::cerr << "No event set for button" << std::endl;
                        }
                        _state = HOVER;
                        return true;
                    }
                } else
                    _state = HOVER;
            } else
                _state = IDLE;
            return false;
        }
        void draw(sf::RenderWindow &window) {
            if (_state == HOVER)
                _text.setFillColor(sf::Color::Red);
            else
                _text.setFillColor(sf::Color::White);
            window.draw(_text);
        }
        void setEvent(std::function<void()> event) {
            _event = event;
        }

    protected:
    private:
        sf::Text _text;
        ButtonState _state = IDLE;
        std::function<void()> _event;
};

#endif /* !BUTTON_HPP_ */
