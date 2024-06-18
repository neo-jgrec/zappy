/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** chunck
*/

#ifndef CHUNCK_HPP_
    #define CHUNCK_HPP_

    #include <SFML/Graphics.hpp>
    #include <vector>
    #include "../../sprites/Sprite.hpp"
    #include <memory>
    #include <utility>

class Chunck {
    public:
        Chunck() {}
        ~Chunck() {}

        sf::Vector2f _pos;
        float _yOffset;
        bool _hover = false;

        void addElement(std::shared_ptr<Sprite> element, sf::Vector2f offset) {
            _enviromentElements.push_back(std::make_pair(element, offset));
        }
        void draw(sf::RenderWindow &window) {
            for (auto element : _enviromentElements) {
                element.first->setPosition(sf::Vector2f(
                    _pos.x + element.second.x,
                    _pos.y + element.second.y - element.first->_sprite.getTexture()->getSize().y / 2 + _yOffset
                ));
                element.first->draw(window);
            }
        }

    private:
        int _food;
        int _linemate;
        int _deraumere;
        int _sibur;
        int _mendiane;
        int _phiras;
        int _thystame;
        std::vector<std::pair<std::shared_ptr<Sprite>, sf::Vector2f>> _enviromentElements;

};

#endif /* !CHUNCK_HPP_ */
