/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Starlings
*/

#ifndef STARLINGS_HPP_
#define STARLINGS_HPP_

    #include <SFML/Graphics.hpp>

    #include "../../utils/Lerp.hpp"
    #include "../../utils/Random.hpp"

class Starlings  {
    public:
        Starlings() {
            _rotation = Random::random(0, 360);
            respawn();
        }

        void respawn() {
            int edge = Random::random(0, 4);
            if (edge == 0)
                _pos = sf::Vector2f(Random::random(0, 1920), 0);
            else if (edge == 1)
                _pos = sf::Vector2f(Random::random(0, 1920), 1080);
            else if (edge == 2)
                _pos = sf::Vector2f(0, Random::random(0, 1080));
            else
                _pos = sf::Vector2f(1920, Random::random(0, 1080));
            edge = Random::random(0, 4);
            if (edge == 0)
                _target = sf::Vector2f(Random::random(0, 1920), 0);
            else if (edge == 1)
                _target = sf::Vector2f(Random::random(0, 1920), 1080);
            else if (edge == 2)
                _target = sf::Vector2f(0, Random::random(0, 1080));
            else
                _target = sf::Vector2f(1920, Random::random(0, 1080));
        }

        void update(float fElapsedTime) {
            _pos = Lerp::moveTo(_pos, _target, 100 * fElapsedTime, 5.f);
            if (_pos.x == _target.x && _pos.y == _target.y)
                respawn();
            _rotation += fElapsedTime * 10;
        }

        float _rotation = 0;
        sf::Vector2f _pos;
        sf::Vector2f _target;
    protected:
    private:
};

#endif /* !STARLINGS_HPP_ */
