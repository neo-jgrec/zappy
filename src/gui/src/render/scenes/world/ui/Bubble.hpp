/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** Bubble
*/

#ifndef BUBBLE_HPP_
#define BUBBLE_HPP_

#include <SFML/Graphics.hpp>
#include <memory>
#include <functional>

class Bubble {
    public:
        Bubble(std::string text, sf::Vector2f pos) {
            _text = text;
            _text = text.substr(0, 20);
            _pos = pos;
        }
        ~Bubble() {
        }

        void update(float fElapsedTime) {
            _time += fElapsedTime;
        }

        bool isFinished() {
            if (_time > 2)
                return true;
            return false;
        }

        sf::Vector2f getPos() { return _pos; }
        std::string getMessage() { return _text; }

    protected:
    private:
        std::string _text;
        sf::Vector2f _pos;
        float _time = 0;
};

#endif /* !BUBBLE_HPP_ */
