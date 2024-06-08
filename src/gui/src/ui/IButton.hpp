/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IButton
*/

#ifndef IBUTTON_HPP_
#define IBUTTON_HPP_

#include <SFML/Graphics.hpp>

class IButton {
    public:
        virtual ~IButton() = default;

        virtual bool update(sf::Event event, sf::RenderWindow &window) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;

    protected:
    private:
};

#endif /* !IBUTTON_HPP_ */
