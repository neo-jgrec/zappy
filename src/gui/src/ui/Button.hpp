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
        void setEvent(std::function<void()> event) { _event = event; }

    protected:
    private:
        sf::Text _text;
        ButtonState _state = IDLE;
        std::function<void()> _event;
};

#endif /* !BUTTON_HPP_ */