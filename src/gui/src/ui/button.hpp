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

class Button : public IButton {
    public:
        Button(sf::Vector2f pos, sf::Vector2f size, std::string text, sf::Font font, sf::Color color, sf::Color textColor);
        ~Button() {}

        bool update(sf::Event event, sf::RenderWindow &window);
        void draw(sf::RenderWindow &window);

    protected:
    private:
        sf::RectangleShape _shape;
        sf::Text _text;
};

#endif /* !BUTTON_HPP_ */
