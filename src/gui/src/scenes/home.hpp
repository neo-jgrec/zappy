/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** home
*/

#ifndef HOME_HPP_
#define HOME_HPP_

#include "IScene.hpp"
#include "../ui/button.hpp"
#include "../ui/input.hpp"

class Home : public IScene {
    public:
        Home(Zappy &zappy) : _zappy(zappy) {
            _title.setFont(zappy.getFont());
            _title.setString("Zappy");
            _title.setPosition(100, 100);
            _title.setCharacterSize(43);

            _quitButton = std::make_shared<Button>(sf::Vector2f(100, 500), sf::Vector2f(100, 100), "Quit", zappy.getFont());
            _startButton = std::make_shared<Button>(sf::Vector2f(100, 400), sf::Vector2f(100, 100), "Start", zappy.getFont());
            _portButton = std::make_shared<Input>(sf::Vector2f(100, 300), sf::Vector2f(100, 100), "Port", zappy.getFont());
            _ipButton = std::make_shared<Input>(sf::Vector2f(100, 200), sf::Vector2f(100, 100), "Ip", zappy.getFont());
        }
        ~Home() {}

        bool update(sf::Event event, sf::RenderWindow &window) override {
            if (_quitButton->update(event, window))
                window.close();
            if (_startButton->update(event, window))
                _zappy._state = GameState::GAME;
            _ipButton->update(event, window);
            _portButton->update(event, window);
            return true;
        }
        void draw(sf::RenderWindow &window) override {
            _quitButton->draw(window);
            _startButton->draw(window);
            _ipButton->draw(window, _zappy.getDeltaTime());
            _portButton->draw(window, _zappy.getDeltaTime());
            window.draw(_title);
        }

    protected:
    private:

        sf::Text _title;
        std::shared_ptr<Button> _quitButton;
        std::shared_ptr<Button> _startButton;

        std::shared_ptr<Input> _ipButton;
        std::shared_ptr<Input> _portButton;

        Zappy &_zappy;
};

#endif /* !HOME_HPP_ */
