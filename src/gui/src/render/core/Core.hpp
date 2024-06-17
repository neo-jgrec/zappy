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

class Core {
    public:
        Core(char **argv, int argc);
        ~Core() {};

        void update();
        void run();

        Zappy _zappy;
    private:

        std::map<GameState, std::shared_ptr<IScene>> _scenes;
        sf::Event _event;
        sf::Clock _clock;

        bool _fullscreen = false;
        sf::Vector2f _resolution = sf::Vector2f(1080, 720);

        // ServerConnect _server;
        // Parser _parser;
        // Data _data;
};

#endif /* !CORE_HPP_ */
