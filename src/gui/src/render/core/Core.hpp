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
    #include "Zappy.hpp"
    #include "../../parser/ServerConnect.hpp"
    #include "../../parser/Parser.hpp"
    #include "../../parser/Data.hpp"
    #include "../../utils/CommandLineParser.hpp"

class Core {
    public:
        Core(char **argv, int argc);
        ~Core() {};

        void update();
        void run();


        void newWindow(sf::Vector2f resolution, bool fullscreen);
        Zappy _zappy;
    private:
        std::map<GameState, std::shared_ptr<IScene>> _scenes;

        sf::RenderWindow _window;
        sf::Event _event;
        sf::Clock _clock;

        ServerConnect _server;
        CommandLineParser _cmdParser;
        Data _data;
        Parser _parser;
};

#endif /* !CORE_HPP_ */
