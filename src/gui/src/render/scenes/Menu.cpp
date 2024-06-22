#include "Menu.hpp"
#include "../core/Core.hpp"

Menu::Menu(Core *core) : _core(core) {
    _fullscreenButton = std::make_shared<Button>(sf::Vector2f(100, 100),
    sf::Vector2f(100, 100), "Windowed", _core->getFont());
    _resolutionButtons.push_back(std::make_shared<Button>(sf::Vector2f(100, 150),
    sf::Vector2f(100, 100), "1920x1080", _core->getFont()));
    _resolutionButtons.push_back(std::make_shared<Button>(sf::Vector2f(300, 150),
    sf::Vector2f(100, 100), "1280x720", _core->getFont()));
    _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", _core->getFont());
    _homeButton = std::make_shared<Button>(sf::Vector2f(100, 450), sf::Vector2f(100, 100), "Home", _core->getFont());
    _homeButton->setCallBack(std::bind(&Menu::getBackHome, this));
    _hzInput = std::make_shared<Input>(sf::Vector2f(100, 200), sf::Vector2f(100, 100), "60", _core->getFont(), "123456789");
    _hzInput->setEnd("Hz");
    _hzInput->setInput("60");
    _funMode = std::make_shared<Button>(sf::Vector2f(100, 250), sf::Vector2f(100, 100), "Fun Mode Off", _core->getFont());
}

bool Menu::update(sf::Event event, sf::RenderWindow &window) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        _core->_upperState = GameState::DEFAULT;
    if (_fullscreenButton->update(event, window)) {
        _core->switchFullscreen();
        _fullscreenButton->setText(_core->isFullscreen() ? "Fullscreen" : "Windowed");
        return true;
    }
    if (_resolutionButtons[0]->update(event, window)) {
        _core->newResolution(sf::Vector2f(1920, 1080));
        return true;
    }
    if (_resolutionButtons[1]->update(event, window)) {
        _core->newResolution(sf::Vector2f(1280, 720));
        return true;
    }
    if (_funMode->update(event, window)) {
        if (_funMode->getText() == "Fun Mode Off")
            _funMode->setText("Fun Mode On");
        else
            _funMode->setText("Fun Mode Off");
        _core->_funMode = !_core->_funMode;
    }
    if (_quitButton->update(event, window))
        window.close();
    _homeButton->update(event, window);
    _hzInput->update(event, window);
    return true;
}

void Menu::draw(sf::RenderWindow &window) {
    _fullscreenButton->draw(window);
    for (auto &button : _resolutionButtons)
        button->draw(window);
    _quitButton->draw(window);
    _homeButton->draw(window);
    _funMode->draw(window);
    _hzInput->draw(window, _core->getDeltaTime());
}

void Menu::getBackHome() {
    if (_core->_server.disconectFromServer() == true)
        _core->_data.resetGame();
    _core->_upperState = GameState::DEFAULT;
    _core->_state = GameState::HOME;
}