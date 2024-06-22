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
    #include "../../core/Setting.hpp"
    #include "../../../utils/Random.hpp"

class Chunck {
    public:
        Chunck() {}
        ~Chunck() {}

        sf::Vector2f _pos;
        float _yOffset;
        bool _hover = false;

        void addElement(std::shared_ptr<Sprite> element) {
            sf::Vector2f offset = sf::Vector2f(
                    Random::random(0, 26) - 13,
                    Random::random(0, 26) - 13
                );
            sf::Vector2f pos = getMiddle() + offset;
            _enviromentElements.push_back(std::make_pair(element, pos));
        }
        void draw(sf::RenderWindow &window) {
            if (_enviromentElements.size() == 1) {
                auto element = _enviromentElements[0];
                element.first->setPosition(element.second);
                element.first->draw(window);
            }
            else if (_enviromentElements.size() == 2) {
                auto element1 = _enviromentElements[0];
                auto element2 = _enviromentElements[1];
                element1.first->setPosition(element1.second);
                element2.first->setPosition(element2.second);

                if (element1.second.y < element2.second.y) {
                    element1.first->draw(window);
                    element2.first->draw(window);
                } else {
                    element2.first->draw(window);
                    element1.first->draw(window);
                }
            }
        }

        sf::Vector2f getMiddle() {
            return sf::Vector2f(
                _pos.x,
                _pos.y + _yOffset - TILE_SIZE_MY
            );
        }

        std::vector<int> _inventory = {0, 0, 0, 0, 0, 0, 0};
        int _nbTrantorians = 0;
    private:
        std::vector<std::pair<std::shared_ptr<Sprite>, sf::Vector2f>> _enviromentElements;

};

#endif /* !CHUNCK_HPP_ */
