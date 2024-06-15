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
#include "../scenes/menu.hpp"
#include "zappy.hpp"
class Core {
    public:
        Core() {
            _window.create(sf::VideoMode( _resolution.x , _resolution.y ), "Zappy", sf::Style::Fullscreen);

            _scenes[GameState::HOME] = std::make_shared<Home>(_zappy);
            _scenes[GameState::END] = std::make_shared<Quit>(_zappy);
            _scenes[GameState::GAME] = std::make_shared<World>(_zappy, sf::Vector2f(15, 15));
            _scenes[GameState::MENU] = std::make_shared<Menu>(_zappy);
            _clock.restart();
        }
        ~Core() {
        }

        void update() {
            if (_event.type == sf::Event::Closed)
                _zappy._upperState = GameState::END;
            if (_event.type == sf::Event::MouseMoved) {
                _zappy.setMousePos(sf::Vector2f(
                    _event.mouseMove.x * 1920 / _window.getSize().x,
                    _event.mouseMove.y * 1080 / _window.getSize().y
                ));
            }
        }

        void run() {
            while (_window.isOpen()) {
                _zappy.setDeltaTime(_clock.getElapsedTime().asSeconds());
                _clock.restart();

                while (_window.pollEvent(_event)) {
                    update();
                    _scenes[((_zappy._upperState != GameState::NONE) ? _zappy._upperState : _zappy._state)]->update(_event, _window);
                    if (_zappy._resolution != _resolution ||
                        _zappy._fullscreen != _fullscreen) {
                        _fullscreen = _zappy._fullscreen;
                        _resolution = _zappy._resolution;
                        _window.create(sf::VideoMode(_resolution.x, _resolution.y), "Zappy", (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
                    }
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

        bool _fullscreen = true;
        sf::Vector2f _resolution = sf::Vector2f(1920, 1080);

};

#endif /* !CORE_HPP_ */
