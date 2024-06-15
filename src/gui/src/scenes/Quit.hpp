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
    #include "../ui/Button.hpp"
    #include "../core/Zappy.hpp"

class Quit : public IScene {
    public:
        Quit(Zappy &zappy);
        ~Quit() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override {
            _quitButton->draw(window);
        }

    protected:
    private:
        std::shared_ptr<Button> _quitButton;
        Zappy &_zappy;
};

#endif /* !QUIT_HPP_ */
