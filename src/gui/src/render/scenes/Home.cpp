#include "Home.hpp"
#include "../core/Core.hpp"

Home::Home(Core *core, int port, std::string ip) : _core(core) {
    _title.setFont(_core->getFont());
    _title.setString("Zappy");
    _title.setPosition(100, 100);
    _title.setCharacterSize(43);

    _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", _core->getFont());
    _startButton = std::make_shared<Button>(sf::Vector2f(100, 300), sf::Vector2f(100, 100), "Start", _core->getFont());
    _portButton = std::make_shared<Input>(sf::Vector2f(100, 250), sf::Vector2f(100, 100), "Port", _core->getFont(),
        "1234567890");
    if (port != 0)
        _portButton->setInput(std::to_string(port));
    _ipButton = std::make_shared<Input>(sf::Vector2f(100, 200), sf::Vector2f(100, 100), "Ip", _core->getFont(),
        "1234567890.");
    if (ip != "")
        _ipButton->setInput(ip);

    _chat = std::make_shared<Chat>(_core->getFont(), 7);
    _chat->setPosition(sf::Vector2f(50, 720 - 50));
    _chat->addMessage("Welcome to Zappy");
}

void Home::draw(sf::RenderWindow &window) {
    _quitButton->draw(window);
    _startButton->draw(window);
    _ipButton->draw(window, _core->getDeltaTime());
    _portButton->draw(window, _core->getDeltaTime());
    _chat->draw(window);
    window.draw(_title);
}

bool Home::update(sf::Event event, sf::RenderWindow &window) {
    if (_quitButton->update(event, window))
        window.close();
    if (_startButton->update(event, window)) {
        int port = 0;
        try {
            port = std::stoi(_portButton->getInput());
        } catch (std::exception &e) {
            _chat->addMessage("Invalid port", sf::Color::Red);
            return false;
        }
        if (!_core->connectToServer(port, _ipButton->getInput())) {
            _chat->addMessage("Failed to connect to server", sf::Color::Red);
            return false;
        }
        _core->_scenes[GameState::GAME]->init();
        _core->_state = GameState::GAME;
    }
    _ipButton->update(event, window);
    _portButton->update(event, window);
    return true;
}
