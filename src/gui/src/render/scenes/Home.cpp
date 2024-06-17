#include "Home.hpp"
#include "../core/Core.hpp"

Home::Home(Core *core) : _core(core) {
    _title.setFont(_core->_zappy.getFont());
    _title.setString("Zappy");
    _title.setPosition(100, 100);
    _title.setCharacterSize(43);

    _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", _core->_zappy.getFont());
    _startButton = std::make_shared<Button>(sf::Vector2f(100, 400), sf::Vector2f(100, 100), "Start", _core->_zappy.getFont());
    _portButton = std::make_shared<Input>(sf::Vector2f(100, 300), sf::Vector2f(100, 100), "Port", _core->_zappy.getFont());
    _ipButton = std::make_shared<Input>(sf::Vector2f(100, 200), sf::Vector2f(100, 100), "Ip", _core->_zappy.getFont());
}
      
void Home::draw(sf::RenderWindow &window) {
    _quitButton->draw(window);
    _startButton->draw(window);
    _ipButton->draw(window, _core->_zappy.getDeltaTime());
    _portButton->draw(window, _core->_zappy.getDeltaTime());
    window.draw(_title);
}

bool Home::update(sf::Event event, sf::RenderWindow &window) {
    if (_quitButton->update(event, window))
        window.close();
    if (_startButton->update(event, window))
        _core->_zappy._state = GameState::GAME;
    _ipButton->update(event, window);
    _portButton->update(event, window);
    return true;
}
