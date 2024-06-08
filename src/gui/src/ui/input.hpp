/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include <string>

#include "../sprites/sprite.hpp"

class Input {
    public:
        Input(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font &font) {
            _placeHolder = text;
            _text.setFont(font);
            _text.setString(text);
            _text.setPosition(pos);
            _text.setCharacterSize(24);
            _text.setFillColor(sf::Color::White);
        }
        ~Input() {}

        bool update(sf::Event event, sf::RenderWindow &window) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            if (_text.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                    _isFocused = true;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!_text.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    _isFocused = false;
            }
            if (_isFocused) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 8) {
                        if (_input.size() > 0)
                            _input.pop_back();
                    } else if (event.text.unicode == 13) {
                        _isFocused = false;
                    } else {
                        _input += event.text.unicode;
                    }
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace) && sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        _input = "";
                    }
                }
            }


            return false;
        }

        void draw(sf::RenderWindow &window, float deltaTime) {
            _time += deltaTime;
            if (!_isFocused && _input.size() == 0)
                _text.setString(_placeHolder);
            else if (_isFocused) {
                if (_time < 0.5)
                    _text.setString(_input + "_");
                else
                    _text.setString(_input);
                if (_time > 1)
                    _time = 0;
            } else {
                _text.setString(_input);
            }

            if (_isFocused)
                _text.setFillColor(sf::Color::Red);
            else
                _text.setFillColor(sf::Color::White);
            window.draw(_text);
        }


        std::string getInput() {
            return _input;
        }

    protected:
    private:
        bool _isFocused = false;
        std::string _input = "";
        std::string _placeHolder = "";
        sf::Text _text;

        float _time = 0;
};

#endif /* !INPUT_HPP_ */
