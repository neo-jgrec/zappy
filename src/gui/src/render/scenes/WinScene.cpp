/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WinScene
*/

#include "WinScene.hpp"
#include "../core/Core.hpp"

WinScene::WinScene(Core *core)
{
    _text.setFont(core->getFont());
    _text.setCharacterSize(25);
    _text.setFillColor(sf::Color::White);
    _core = core;
    _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", _core->getFont());
    _homeButton = std::make_shared<Button>(sf::Vector2f(100, 450), sf::Vector2f(100, 100), "Home", _core->getFont());
    _homeButton->setCallBack(std::bind(&WinScene::getBackHome, this));
    _win = std::make_shared<Sprite>("./assets/win.png");
    _win->setScale(1.5f);
}

void WinScene::draw(sf::RenderWindow &window)
{
    sf::Vector2f winSize = window.getView().getSize();
    _quitButton->setPosition(sf::Vector2f(winSize.x / 2 - 150, winSize.y / 2 + 150));
    _homeButton->setPosition(sf::Vector2f(winSize.x / 2 + 50, winSize.y / 2 + 150));
    _quitButton->draw(window);
    _homeButton->draw(window);
    _text.setPosition(sf::Vector2f(winSize.x / 2 -_text.getGlobalBounds().width / 2
        , winSize.y / 2 + 100));
    _text.setString(_core->_winner + " won the game !");
    _win->setPosition(sf::Vector2f(winSize.x / 2, winSize.y / 2 - 100));
    window.draw(_text);
    _win->draw(window);
}

void WinScene::getBackHome()
{
    if (_core->_server.disconectFromServer() == true)
        _core->_data.resetGame();
    _core->_upperState = GameState::DEFAULT;
    _core->_state = GameState::HOME;
}
