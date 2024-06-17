/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Lerp
*/

#ifndef LERP_HPP_
#define LERP_HPP_

#include <SFML/Graphics.hpp>
#include <cmath>

class Lerp {
    public:
        Lerp() {}
        ~Lerp() {}

        static float lerp(float a, float b, float t) {
            return a + t * (b - a);
        }

        static sf::Vector2f lerp(sf::Vector2f a, sf::Vector2f b, float t, float distanceThreshold = 0.1f) {
            float distance = std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
            if (distance < distanceThreshold) {
                return b;
            } else {
                return sf::Vector2f(lerp(a.x, b.x, t), lerp(a.y, b.y, t));
            }
        }

        static sf::Color lerp(sf::Color a, sf::Color b, float t) {
            return sf::Color(
                lerp(a.r, b.r, t),
                lerp(a.g, b.g, t),
                lerp(a.b, b.b, t),
                lerp(a.a, b.a, t)
            );
        }
};

#endif /* !LERP_HPP_ */
