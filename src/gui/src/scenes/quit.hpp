/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** quit
*/

#ifndef QUIT_HPP_
#define QUIT_HPP_

#include <memory>

#include "IScene.hpp"
#include "../ui/button.hpp"

class Quit : public IScene {
    public:
        Quit(Zappy &zappy) : _zappy(zappy) {
            _quitButton = std::make_shared<Button>(sf::Vector2f(1080 / 2, 720 / 2),
            sf::Vector2f(100, 100), "Quit", zappy.getFont());
        }
        ~Quit() {}

        bool update(sf::Event event, sf::RenderWindow &window) override {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                _zappy._upperState = GameState::NONE;
            if (_quitButton->update(event, window))
                window.close();
            return true;
        }
        void draw(sf::RenderWindow &window) override {
            _quitButton->draw(window);
        }

    protected:
    private:
        std::shared_ptr<Button> _quitButton;
        Zappy &_zappy;
};

#endif /* !QUIT_HPP_ */
