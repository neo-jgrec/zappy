#include "Button.hpp"

#include <iostream>

Button::Button(sf::Vector2f pos, [[maybe_unused]] sf::Vector2f size, std::string text, sf::Font &font) {
    _text.setFont(font);
    _text.setString(text);
    _text.setPosition(pos);
    _text.setCharacterSize(24);
    _text.setFillColor(sf::Color::White);
}

bool Button::update(sf::Event event, sf::RenderWindow &window) {
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

void Button::draw(sf::RenderWindow &window) {
    if (_state == HOVER)
        _text.setFillColor(sf::Color::Red);
    else
        _text.setFillColor(sf::Color::White);
    window.draw(_text);
}
