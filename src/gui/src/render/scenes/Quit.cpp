#include "Quit.hpp"
#include "../core/Core.hpp"

Quit::Quit(Core *core) : _core(core) {
    _quitButton = std::make_shared<Button>(sf::Vector2f(1080 / 2, 720 / 2),
    sf::Vector2f(100, 100), "Quit", _core->getFont());
}

bool Quit::update(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _core->_upperState = GameState::DEFAULT;
    if (_quitButton->update(event, window))
        window.close();
    return true;
}
