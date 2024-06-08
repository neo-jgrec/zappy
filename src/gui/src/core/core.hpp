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

#include "../world/world.hpp"
#include "../sprites/sprite.hpp"

class Core {
    public:
        Core() {
            _window.create(sf::VideoMode( 1280 , 720 ), "Zappy");
            _world = std::make_shared<World>(sf::Vector2i(15, 15));

            auto grass = std::make_shared<Sprite>("./assets/Sprites/Enviroument/Spring/grass.png");
            _sprites["grass"] = grass;
            _isMousePressed = false;
        }
        ~Core() {
        }

        void init() {
            _world->init(_sprites);
            run();
        }

        void run() {
            while (_window.isOpen()) {
                update();
                _world->draw(_window);
                _window.display();
            }
        }

        void update() {
            sf::Event event;
            while (_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    _window.close();
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        std::cout << "Mouse pressed" << std::endl;
                        _isMousePressed = true;
                        _mousePos = (sf::Vector2f)sf::Mouse::getPosition(_window);
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        _isMousePressed = false;
                        _world->move(_deltaMousePos);
                        _world->_offset = sf::Vector2f(0, 0);
                    }
                }
                if (_isMousePressed) {
                    _deltaMousePos = (sf::Vector2f)sf::Mouse::getPosition(_window) - _mousePos;
                    _world->_offset = _deltaMousePos;
                }
                if (event.type == sf::Event::KeyPressed)
                    if (event.key.code == sf::Keyboard::Space)
                        _world->reset();
            }
            _window.clear(sf::Color(100, 100, 100));
        }

    private:
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;
        sf::RenderWindow _window;
        std::shared_ptr<World> _world;

        float _deltaTime;
        sf::Clock _clock;
        sf::Vector2f _mousePos;
        sf::Vector2f _deltaMousePos;
        bool _isMousePressed;
};

#endif /* !CORE_HPP_ */
