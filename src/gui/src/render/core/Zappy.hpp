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
    DEFAULT,
};

class Core;
class Zappy {
    public:
        Zappy(Core *core)
            : _core(core) {
            _font.loadFromFile("assets/BadComic-Regular.ttf");
            _state = GameState::HOME;
            _upperState = GameState::DEFAULT;
        };
        ~Zappy() {};

        GameState _state;
        GameState _upperState;

        sf::Font &getFont() { return _font; };
        void setDeltaTime(float deltaTime) { _deltaTime = deltaTime; };
        float getDeltaTime() { return _deltaTime; };
        void setMousePos(sf::Vector2f mousePos) { _mousePos = mousePos; };
        sf::Vector2f getMousePos() { return _mousePos; };

        sf::Vector2f _resolution = sf::Vector2f(1280, 720);
        bool _fullscreen = false;
    protected:
    private:
        sf::Font _font;
        float _deltaTime = 0;
        sf::Vector2f _mousePos;
        Core *_core;


};

#endif /* !ZAPPY_HPP_ */
