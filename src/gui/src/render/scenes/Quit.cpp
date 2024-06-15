#include "Quit.hpp"

Quit::Quit(Zappy &zappy) : _zappy(zappy) {
    _quitButton = std::make_shared<Button>(sf::Vector2f(1080 / 2, 720 / 2),
    sf::Vector2f(100, 100), "Quit", zappy.getFont());
}

bool Quit::update(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
        window.close();
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _zappy._upperState = GameState::DEFAULT;
    if (_quitButton->update(event, window))
        window.close();
    return true;
}
