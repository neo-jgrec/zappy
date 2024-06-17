/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
    #define ISCENE_HPP_

    #include <SFML/Graphics.hpp>

class IScene {
    public:
        virtual ~IScene() = default;

        virtual bool update(sf::Event event, sf::RenderWindow &window) = 0;
        virtual void draw(sf::RenderWindow &window) = 0;
        virtual void init() = 0;

    protected:
    private:
};

#endif /* !ISCENE_HPP_ */
