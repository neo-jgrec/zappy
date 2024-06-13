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
            _window.create(sf::VideoMode( 1080 , 720 ), "Zappy", sf::Style::Default);
            // _window.create(sf::VideoMode( 1920 , 1080 ), "Zappy", sf::Style::Default);
            // _window.setFramerateLimit(60);
            // _window.setVerticalSyncEnabled(true);

            _scenes[GameState::HOME] = std::make_shared<Home>(_zappy);
            _scenes[GameState::END] = std::make_shared<Quit>(_zappy);
            _scenes[GameState::GAME] = std::make_shared<World>(_zappy, sf::Vector2f(15, 15));
            _clock.restart();
        }
        ~Core() {
        }

        void update() {
            if (_event.type == sf::Event::Closed)
                _zappy._upperState = GameState::END;
            if (_event.type == sf::Event::MouseMoved) {
                // _zappy.setMousePos(
                //     _window.mapPixelToCoords(sf::Mouse::getPosition(_window))
                // );
                _zappy.setMousePos(sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y));
            }
        }

        void run() {
            while (_window.isOpen()) {
                _zappy.setDeltaTime(_clock.getElapsedTime().asSeconds());
                _clock.restart();

                while (_window.pollEvent(_event)) {
                    update();
                    _scenes[((_zappy._upperState != GameState::NONE) ? _zappy._upperState : _zappy._state)]->update(_event, _window);
                }
                _window.clear(sf::Color(100, 100, 100));

                _scenes[_zappy._state]->draw(_window);
                if (_zappy._upperState != GameState::NONE)
                    _scenes[_zappy._upperState]->draw(_window);
                _window.display();
            }
        }

        Zappy _zappy;
    private:
        sf::RenderWindow _window;

        std::map<GameState, std::shared_ptr<IScene>> _scenes;
        sf::Event _event;
        sf::Clock _clock;

};

#endif /* !CORE_HPP_ */
