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

class Core;
class Quit : public IScene {
    public:
        Quit(Core *core);
        ~Quit() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float /*fElapsedTime*/) override {}
        void draw(sf::RenderWindow &window) override {
            _quitButton->draw(window);
        }
        void init() override {}

    protected:
    private:
        std::shared_ptr<Button> _quitButton;
        Core *_core;
};

#endif /* !QUIT_HPP_ */
