/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** diamond
*/

#ifndef DIAMOND_HPP_
    #define DIAMOND_HPP_

    #include <SFML/Graphics.hpp>

class Diamond {
    public:
        Diamond() {};
        Diamond(sf::Vector2f tileSize) {
            _tileSize = tileSize;
            _triangle1.setPointCount(3);
            _triangle1.setPoint(0, sf::Vector2f(_tileSize.x / 2, 0));
            _triangle1.setPoint(1, sf::Vector2f(_tileSize.x, _tileSize.y / 4 + 1));
            _triangle1.setPoint(2, sf::Vector2f(_tileSize.x / 2, _tileSize.y / 2 + 1));
            _triangle1.setFillColor(sf::Color::Green);
            _triangle2.setPointCount(3);
            _triangle2.setPoint(0, sf::Vector2f(_tileSize.x / 2, 0));
            _triangle2.setPoint(1, sf::Vector2f(0, _tileSize.y / 4 + 1));
            _triangle2.setPoint(2, sf::Vector2f(_tileSize.x / 2, _tileSize.y / 2 + 1));
            _triangle2.setFillColor(sf::Color::Blue);
        }
        ~Diamond() {};

        void draw(sf::RenderWindow &window) {
            window.draw(_triangle1);
            window.draw(_triangle2);
        }

        float crossProduct(sf::Vector2f a, sf::Vector2f b) {
            return (a.x * b.y - a.y * b.x);
        }

        bool checkTriangle(sf::ConvexShape triangle, const sf::Vector2f& mousePos) {
            sf::Vector2f v1 = triangle.getPoint(0) + _pos;
            sf::Vector2f v2 = triangle.getPoint(1) + _pos;
            sf::Vector2f v3 = triangle.getPoint(2) + _pos;

            sf::Vector2f d1 = v2 - v1;
            sf::Vector2f d2 = v3 - v2;
            sf::Vector2f d3 = v1 - v3;

            sf::Vector2f c1 = mousePos - v1;
            sf::Vector2f c2 = mousePos - v2;
            sf::Vector2f c3 = mousePos - v3;

            float cross1 = crossProduct(d1, c1);
            float cross2 = crossProduct(d2, c2);
            float cross3 = crossProduct(d3, c3);

            bool hasNeg = (cross1 < 0) || (cross2 < 0) || (cross3 < 0);
            bool hasPos = (cross1 > 0) || (cross2 > 0) || (cross3 > 0);

            return !(hasNeg && hasPos);
        }

        bool checkCollision(sf::Vector2f mousePos) {
            if (checkTriangle(_triangle1, mousePos) || checkTriangle(_triangle2, mousePos))
                return (true);
            return (false);
        }

        void setPosition(sf::Vector2f pos) {
            _pos = sf::Vector2f(pos.x - _tileSize.x / 2, pos.y - _tileSize.y / 2);
            _triangle1.setPosition(_pos);
            _triangle2.setPosition(_pos);
        }

        void setColor(sf::Color color) {
            _triangle1.setFillColor(color);
            _triangle2.setFillColor(color);
        }

    private:
        sf::Vector2f _pos = sf::Vector2f(0, 0);
        sf::Vector2f _tileSize;
        sf::ConvexShape _triangle1;
        sf::ConvexShape _triangle2;

};


#endif /* !DIAMOND_HPP_ */