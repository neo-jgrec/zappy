/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include <memory>

#include "../scenes/world/world.hpp"
#include "../sprites/sprite.hpp"
#include "../scenes/home.hpp"
#include "../scenes/quit.hpp"
#include "zappy.hpp"

class Core {
    public:
        Core() {
            _window.create(sf::VideoMode( 1280 , 720 ), "Zappy");
            // _world = std::make_shared<World>(sf::Vector2i(15, 15));

            // auto grass = std::make_shared<Sprite>("./assets/grass.png");
            // _sprites["grass"] = grass;
            // _isMousePressed = false;
            // _world->init(_sprites);

            _scenes[GameState::HOME] = std::make_shared<Home>(_zappy);
            _scenes[GameState::END] = std::make_shared<Quit>(_zappy);
            _scenes[GameState::GAME] = std::make_shared<World>(sf::Vector2i(15, 15));
        }
        ~Core() {
        }

        void checkClose() {
            if (_event.type == sf::Event::Closed)
                _zappy._upperState = GameState::END;

        }

        void run() {
            while (_window.isOpen()) {
                while (_window.pollEvent(_event)) {
                    checkClose();
                    _scenes[((_zappy._upperState != GameState::NONE) ? _zappy._upperState : _zappy._state)]->update(_event, _window);
                }
                _window.clear(sf::Color(100, 100, 100));

                _scenes[_zappy._state]->draw(_window);
                if (_zappy._upperState != GameState::NONE)
                    _scenes[_zappy._upperState]->draw(_window);
                _window.display();
            }
        }

    private:
        sf::RenderWindow _window;

        Zappy _zappy;
        std::map<GameState, std::shared_ptr<IScene>> _scenes;
        sf::Event _event;

};

#endif /* !CORE_HPP_ */
