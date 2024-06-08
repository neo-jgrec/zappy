/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** zappy
*/

#ifndef ZAPPY_HPP_
#define ZAPPY_HPP_

#include <SFML/Graphics.hpp>

enum GameState {
    HOME,
    MENU,
    GAME,
    QUIT,
    END,
    NONE,
};

class Zappy {
    public:
        Zappy() {
            _font.loadFromFile("assets/BadComic-Regular.ttf");
            _state = GameState::HOME;
            _upperState = GameState::NONE;
        };
        ~Zappy() {};

        sf::Font &getFont() { return _font; };
        GameState _state;
        GameState _upperState;

        void setDeltaTime(float deltaTime) { _deltaTime = deltaTime; };
        float getDeltaTime() { return _deltaTime; };
    protected:
    private:
        sf::Font _font;
        float _deltaTime = 0;

};

#endif /* !ZAPPY_HPP_ */
