#include "Home.hpp"
#include "../core/Core.hpp"

Home::Home(Core *core, int port, std::string ip) : _core(core) {

    _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", _core->getFont());
    _startButton = std::make_shared<Button>(sf::Vector2f(100, 400), sf::Vector2f(100, 100), "Start", _core->getFont());
    _portButton = std::make_shared<Input>(sf::Vector2f(100, 350), sf::Vector2f(100, 100), "Port", _core->getFont(),
        "1234567890");
    if (port != 0)
        _portButton->setInput(std::to_string(port));
    _ipButton = std::make_shared<Input>(sf::Vector2f(100, 300), sf::Vector2f(100, 100), "Ip", _core->getFont(),
        "1234567890.");
    if (ip != "")
        _ipButton->setInput(ip);

    _chat = std::make_shared<Chat>(_core->getFont(), 7);
    _chat->setPosition(sf::Vector2f(50, 720 - 50));
    _chat->addMessage("Welcome to Zappy 1.0");
    initSprites();
}

void Home::draw(sf::RenderWindow &window) {
    _sprites["background"]->draw(window);
    _sprites["movingEarth"]->draw(window);
    for (auto &starling : _starlings) {
        _sprites["starling"]->setPosition(starling._pos);
        _sprites["starling"]->setRotation(starling._rotation);
        _sprites["starling"]->draw(window);
    }
    _quitButton->draw(window);
    _startButton->draw(window);
    _ipButton->draw(window, _core->getDeltaTime());
    _portButton->draw(window, _core->getDeltaTime());
    _chat->draw(window);
    _sprites["logo"]->draw(window);
}

void Home::update(float fElapsedTime) {
    _sprites["movingEarth"]->update(fElapsedTime);
    for (auto &starling : _starlings) {
        starling.update(fElapsedTime);
    }
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

void Home::initSprites() {
    _sprites["background"] = std::make_shared<Sprite>("assets/background.jpg");
    _sprites["background"]->resetOrigin();
    _sprites["movingEarth"] = std::make_shared<Sprite>("assets/earthPlanetMenu75.png", 100, 0.3f);
    _sprites["movingEarth"]->setScale(10);
    _sprites["logo"] = std::make_shared<Sprite>("assets/logo.png");
    _sprites["logo"]->setPosition(sf::Vector2f(200, 150));
    _sprites["movingEarth"]->setPosition(sf::Vector2f(1080, 720));
    _sprites["starling"] = std::make_shared<Sprite>("assets/trantorian.png");
    _sprites["starling"]->setScale(2);
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
    _starlings.push_back(Starlings());
}