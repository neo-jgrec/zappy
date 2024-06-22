/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#include "Input.hpp"

Input::Input(sf::Vector2f pos, [[maybe_unused]] sf::Vector2f size, std::string text, sf::Font &font, std::string accept)
    : _accept(accept)
{
    _placeHolder = text;
    _text.setFont(font);
    _text.setString(text);
    _text.setPosition(pos);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
}

bool Input::update(sf::Event event, sf::RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (!_isFocused)
        _hover = _text.getGlobalBounds().contains(mousePos.x, mousePos.y);
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
        _isFocused = _text.getGlobalBounds().contains(mousePos.x, mousePos.y);
    if (_isFocused) {
        if (event.type == sf::Event::TextEntered) {
            if (event.text.unicode == 8) {
                if (_input.size() > 0)
                    _input.pop_back();
            } else if (event.text.unicode == 13) {
                _isFocused = false;
            } else {
                if (_accept.find(event.text.unicode) != std::string::npos)
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

void Input::draw(sf::RenderWindow &window, float deltaTime) {
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

    if (_isFocused || _hover)
        _text.setFillColor(sf::Color::Red);
    else
        _text.setFillColor(sf::Color::White);
    window.draw(_text);
}
