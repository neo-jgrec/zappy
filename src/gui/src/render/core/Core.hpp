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

        std::map<GameState, std::shared_ptr<IScene>> _scenes;
        float getDeltaTime() { return _deltaTime; };
        sf::Font &getFont() { return _font; };
        sf::Vector2f getMousePos() { return _mousePos; };
        sf::Vector2f getRealMousePos() { return _realMousePos; };

        bool connectToServer(int port, std::string ip);
        Data _data;
        Parser _parser;
        ServerConnect _server;
    private:

        sf::RenderWindow _window;
        sf::Event _event;
        sf::Clock _clock;
        float _deltaTime;
        sf::Vector2f _mousePos;
        sf::Vector2f _realMousePos;


        sf::Font _font;
        sf::Vector2f _resolution = sf::Vector2f(1280, 720);
        bool _fullscreen = false;
        sf::RectangleShape _shade;
};

#endif /* !CORE_HPP_ */
