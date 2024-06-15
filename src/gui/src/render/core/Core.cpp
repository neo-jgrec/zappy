#include "Core.hpp"

#include "../scenes/world/World.hpp"
#include "../scenes/Home.hpp"
#include "../scenes/Quit.hpp"
#include "../scenes/Menu.hpp"

Core::Core() {
    _window.create(sf::VideoMode( _resolution.x , _resolution.y ), "Zappy", sf::Style::Close);

    _scenes[GameState::HOME] = std::make_shared<Home>(_zappy);
    _scenes[GameState::END] = std::make_shared<Quit>(_zappy);
    _scenes[GameState::GAME] = std::make_shared<World>(_zappy, sf::Vector2f(15, 15));
    _scenes[GameState::MENU] = std::make_shared<Menu>(_zappy);
    _clock.restart();
}

void Core::update() {
    if (_event.type == sf::Event::Closed)
        _zappy._upperState = GameState::END;
    if (_event.type == sf::Event::MouseMoved) {
        _zappy.setMousePos(sf::Vector2f(
            _event.mouseMove.x * 1920 / _window.getSize().x,
            _event.mouseMove.y * 1080 / _window.getSize().y
        ));
    }
}

void Core::run() {
    while (_window.isOpen()) {
        _zappy.setDeltaTime(_clock.getElapsedTime().asSeconds());
        _clock.restart();

        while (_window.pollEvent(_event)) {
            update();
            _scenes[((_zappy._upperState != GameState::DEFAULT) ? _zappy._upperState : _zappy._state)]->update(_event, _window);
            if (_zappy._resolution != _resolution ||
                _zappy._fullscreen != _fullscreen) {
                _fullscreen = _zappy._fullscreen;
                _resolution = _zappy._resolution;
                _window.create(sf::VideoMode(_resolution.x, _resolution.y), "Zappy", (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
            }
        }
        _window.clear(sf::Color(100, 100, 100));

        _scenes[_zappy._state]->draw(_window);
        if (_zappy._upperState != GameState::DEFAULT)
            _scenes[_zappy._upperState]->draw(_window);
        _window.display();
    }
}
