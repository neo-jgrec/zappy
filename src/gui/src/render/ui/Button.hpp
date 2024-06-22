/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_

    #include <SFML/Graphics.hpp>
    #include <functional>

enum ButtonState {
    IDLE,
    HOVER,
    CLICKED,
};

class Button {
    public:
        Button(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font &font);
        ~Button() {};

        bool update(sf::Event event, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);
        void setCallBack(std::function<void()> event) { _event = event; }

        void setFontSize(int size) {
            _text.setCharacterSize(size);
        }

        void setText(std::string text) {
            _text.setString(text);
        }

        std::string getText() {
            return _text.getString();
        }

    protected:
    private:
        sf::Text _text;
        ButtonState _state = IDLE;
        std::function<void()> _event;
};

#endif /* !BUTTON_HPP_ */
