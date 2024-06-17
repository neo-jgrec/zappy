/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_

    #include <memory>

    #include "../scenes/IScene.hpp"
    #include "../../parser/ServerConnect.hpp"
    #include "../../parser/Parser.hpp"
    #include "../../parser/Data.hpp"
    #include "../../utils/CommandLineParser.hpp"

enum GameState {
    HOME,
    MENU,
    GAME,
    QUIT,
    END,
    DEFAULT,
};
class Core {
    public:
        Core(int port, std::string ip);
        ~Core() {};

        void update();
        void run();
        void draw();

        void newResolution(sf::Vector2f resolution);
        void switchFullscreen();

        GameState _state;
        GameState _upperState;

        float getDeltaTime() { return _deltaTime; };
        sf::Font &getFont() { return _font; };
        sf::Vector2f getMousePos() { return _mousePos; };
    private:
        std::map<GameState, std::shared_ptr<IScene>> _scenes;

        sf::RenderWindow _window;
        sf::Event _event;
        sf::Clock _clock;
        float _deltaTime;
        sf::Vector2f _mousePos;

        ServerConnect _server;
        Data _data;
        Parser _parser;

        sf::Font _font;
        sf::Vector2f _resolution = sf::Vector2f(1280, 720);
        bool _fullscreen = false;
};

#endif /* !CORE_HPP_ */
