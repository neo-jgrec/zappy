#include "Core.hpp"

#include "../scenes/world/World.hpp"
#include "../scenes/Home.hpp"
#include "../scenes/Quit.hpp"
#include "../scenes/Menu.hpp"
#include "../scenes/WinScene.hpp"
#include <iostream>
#include "../../utils/GuiException.hpp"

Core::Core(int port, std::string ip) {
    _window.create(
        sf::VideoMode(_resolution.x , _resolution.y),
        "Zappy",
        sf::Style::Close);
    _font.loadFromFile("assets/BadComic-Regular.ttf");
    _state = GameState::HOME;
    _upperState = GameState::DEFAULT;
    _shade = sf::RectangleShape(sf::Vector2f(1920, 1080));
    _shade.setFillColor(sf::Color(0, 0, 0, 150));

    _scenes[GameState::HOME] = std::make_shared<Home>(this, port, ip);
    _scenes[GameState::END] = std::make_shared<Quit>(this);
    _scenes[GameState::GAME] = std::make_shared<World>(this);
    _scenes[GameState::MENU] = std::make_shared<Menu>(this);
    _scenes[GameState::WIN] = std::make_shared<WinScene>(this);
    _clock.restart();
    initSounds();
    _sounds["music"].play();
    std::cout << "play music" << std::endl;

    if (!_cursorTexture.loadFromFile("assets/cursor.png"))
        throw guiException("Failed to load cursor");
    _cursor.setTexture(_cursorTexture);
    _window.setMouseCursorVisible(false);
    initIcon();
}

void Core::update() {
    _deltaTime = _clock.getElapsedTime().asSeconds();
    _clock.restart();

    while (_window.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _upperState = GameState::END;
        if (_event.type == sf::Event::MouseMoved) {
            _realMousePos = sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y);
            if (_state == GameState::GAME) {
                _mousePos = sf::Vector2f(
                    _event.mouseMove.x * 1920 / _window.getSize().x,
                    _event.mouseMove.y * 1080 / _window.getSize().y
                );
            } else
                _mousePos = sf::Vector2f(_event.mouseMove.x, _event.mouseMove.y);
        }
        _scenes[
            ((_upperState != GameState::DEFAULT) ? _upperState : _state)
            ]->update(_event, _window);
    }
    _scenes[
            ((_upperState != GameState::DEFAULT) ? _upperState : _state)
            ]->update(_deltaTime);
}

void Core::run() {
    while (_window.isOpen()) {
        _parser.updateData(_data, _server);
        auto players = _data.getPlayers();
        for (auto &player : players)
            player.second->getNextEvent();
        update();
        draw();
    }
}

void Core::draw() {
    _window.clear(sf::Color(82,198,255));

    _scenes[_state]->draw(_window);
    if (_upperState != GameState::DEFAULT) {
        _window.draw(_shade);
        _scenes[_upperState]->draw(_window);
    }
    _cursor.setPosition(_window.mapPixelToCoords(sf::Mouse::getPosition(_window)));
    _window.draw(_cursor);
    _window.display();
}

void Core::newResolution(sf::Vector2f resolution) {
    if (resolution.x == _resolution.x && resolution.y == _resolution.y)
        return;
    _resolution = resolution;
    _window.create(
        sf::VideoMode(_resolution.x, _resolution.y),
        "Zappy",
        (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Close);
    _window.setMouseCursorVisible(false);
}

void Core::switchFullscreen() {
    _fullscreen = !_fullscreen;
    _window.create(
        sf::VideoMode(_resolution.x, _resolution.y),
        "Zappy",
        (_fullscreen) ? sf::Style::Fullscreen : sf::Style::Close);
    _window.setMouseCursorVisible(false);
}

bool Core::connectToServer(int port, std::string ip) {
    try {
        _server.connectToServer(port, ip.c_str());
    } catch (guiException &e) {
        return false;
    }
    return true;
}

void Core::backToHome() {
    if (_server.disconectFromServer() == true)
        _data.resetGame();
    _upperState = GameState::DEFAULT;
    _state = GameState::HOME;
}

void Core::initSounds() {
    _music.openFromFile("assets/audio/music.ogg");
    _music.setLoop(true);
    _music.play();
}

void Core::initIcon() {
    try {
        sf::Image icon;
        icon.loadFromFile("assets/icon.png");
        _window.setIcon(32, 32, icon.getPixelsPtr());
    } catch (const std::exception &e) {
        std::cerr << "Failed to set icon" << std::endl;
    }
}