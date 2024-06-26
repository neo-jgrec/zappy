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

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>

enum GameState {
    HOME,
    MENU,
    GAME,
    QUIT,
    END,
    WIN,
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
        sf::RenderWindow &getWindow() { return _window; };

        bool connectToServer(int port, std::string ip);
        void backToHome();
        Data _data;
        Parser _parser;
        ServerConnect _server;
        std::map<std::string, sf::Sound> _sounds;
        bool isFullscreen() { return _fullscreen; }
        int _tickRate = 2;

        bool _funMode = false;
        std::string _winner = "";
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

        sf::Music _music;
        sf::Texture _cursorTexture;
        sf::Sprite _cursor;

        void initSounds();
        void initCursor();
        void initIcon();
};

#endif /* !CORE_HPP_ */
