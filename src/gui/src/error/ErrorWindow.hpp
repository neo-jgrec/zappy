/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** ErrorWindow
*/

#ifndef ERRORWINDOW_HPP_
#define ERRORWINDOW_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


static const std::vector<std::string> errorTitles = {
    "Error: Initialization failed",
    "Error: Runtime error",
};

static const std::vector<std::string> errorMessages = {
    "uh oh, something went wrong during \nthe initialization of the game, \nplease check the logs\n or reinstall the game",
    "uh oh, something went wrong during \nthe runtime of the game, \nplease check the logs\n or reinstall the game",
};

class ErrorWindow {

    public:
        ErrorWindow(int errorType) {
            if (errorType < 0 || errorType > 1)
                errorType = 0;
            _errorType = errorType;
            _window.create(sf::VideoMode(400, 225), errorTitles[_errorType], sf::Style::Close);
            if (_font.loadFromFile("assets/BadComic-Regular.ttf") == false)
                throw std::runtime_error("Error: Font not found");
            _text.setFont(_font);
            _text.setString(errorMessages[_errorType]);
            _text.setCharacterSize(15);
            _text.setPosition(0, 0);

            if (_texture.loadFromFile("assets/error.png") == false)
                throw std::runtime_error("Error: Texture not found");
            _sprite.setTexture(_texture);
            _sprite.setPosition(
                400 / 2 - 140 / 2
                , 225 - 140
            );

        };
        ~ErrorWindow() {};

        void run() {
            while (_window.isOpen()) {
                sf::Event event;
                while (_window.pollEvent(event)) {
                    if (event.type == sf::Event::Closed)
                        _window.close();
                }
                _window.clear();
                _window.draw(_text);
                _window.draw(_sprite);
                _window.display();
            }
        }
    protected:
    private:
        int _errorType = 0;
        sf::Font _font;
        sf::Text _text;
        sf::Texture _texture;
        sf::Sprite _sprite;
        sf::RenderWindow _window;
};

#endif /* !ERRORWINDOW_HPP_ */
