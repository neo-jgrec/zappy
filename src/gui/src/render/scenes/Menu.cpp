#include "Menu.hpp"

Menu::Menu(Zappy &zappy) : _zappy(zappy) {
    _fullscreenButton = std::make_shared<Button>(sf::Vector2f(1080 / 2, 720 / 2),
    sf::Vector2f(100, 100), "Fullscreen", zappy.getFont());
    _resolutionButtons.push_back(std::make_shared<Button>(sf::Vector2f(1080 / 2, 720 / 2 + 100),
    sf::Vector2f(100, 100), "1920x1080", zappy.getFont()));
    _resolutionButtons.push_back(std::make_shared<Button>(sf::Vector2f(1080 / 2 + 100, 720 / 2 + 100),
    sf::Vector2f(100, 100), "1280x720", zappy.getFont()));
    _resolutionButtons.push_back(std::make_shared<Button>(sf::Vector2f(1080 / 2 + 200, 720 / 2 + 100),
    sf::Vector2f(100, 100), "800x600", zappy.getFont()));
}

bool Menu::update(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _zappy._upperState = GameState::GAME;
    if (_fullscreenButton->update(event, window)) {
        _zappy._fullscreen = !_zappy._fullscreen;
        return true;
    }
    if (_resolutionButtons[0]->update(event, window)) {
        _zappy._resolution = sf::Vector2f(1920, 1080);
        return true;
    }
    if (_resolutionButtons[1]->update(event, window)) {
        _zappy._resolution = sf::Vector2f(1280, 720);
        return true;
    }
    if (_resolutionButtons[2]->update(event, window)) {
        _zappy._resolution = sf::Vector2f(800, 450);
        return true;
    }
    return true;
}

void Menu::draw(sf::RenderWindow &window) {
    _fullscreenButton->draw(window);
    for (auto &button : _resolutionButtons)
        button->draw(window);
}
