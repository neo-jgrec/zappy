#include "Core.hpp"

#include "../scenes/world/World.hpp"
#include "../scenes/Home.hpp"
#include "../scenes/Quit.hpp"
#include "../scenes/Menu.hpp"

Core::Core(char **argv, int argc) {
    _zappy._window.create(sf::VideoMode( _resolution.x , _resolution.y ), "Zappy", sf::Style::Close);

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
        if (_zappy._state == GameState::GAME)
            _zappy.setMousePos(sf::Vector2f(
                _event.mouseMove.x * 1920 / _zappy._window.getSize().x,
                _event.mouseMove.y * 1080 / _zappy._window.getSize().y
            ));
        else
            _zappy.setMousePos(sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y));
    }

}

void Core::run() {
    while (_zappy._window.isOpen()) {
        _zappy.setDeltaTime(_clock.getElapsedTime().asSeconds());
        _clock.restart();

        while (_zappy._window.pollEvent(_event)) {
            update();
            _scenes[((_zappy._upperState != GameState::DEFAULT) ? _zappy._upperState : _zappy._state)]->update(_event, _zappy._window);
            if (_zappy._resolution != _resolution ||
                _zappy._fullscreen != _fullscreen) {
                _fullscreen = _zappy._fullscreen;
                _resolution = _zappy._resolution;
                _zappy._window.create(sf::VideoMode(_resolution.x, _resolution.y), "Zappy", (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Default);
            }
        }
        _zappy._window.clear(sf::Color(82,198,255));

        _scenes[_zappy._state]->draw(_zappy._window);
        if (_zappy._upperState != GameState::DEFAULT)
            _scenes[_zappy._upperState]->draw(_zappy._window);
        _zappy._window.display();
    }
}
