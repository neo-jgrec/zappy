/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** quit
*/

#ifndef MENU_HPP_
    #define MENU_HPP_

    #include <memory>

    #include "IScene.hpp"
    #include "../ui/Button.hpp"
    #include "../ui/Input.hpp"

class Core;
class Menu : public IScene {
    public:
        Menu(Core *core);
        ~Menu() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float /*fElapsedTime*/) override {}
        void draw(sf::RenderWindow &window) override;
        void init() override  {}
        void createHzButtons();
        void getBackHome();
    protected:
    private:
        std::vector<std::shared_ptr<Button>> _resolutionButtons;
        std::shared_ptr<Button> _fullscreenButton;
        std::shared_ptr<Button> _homeButton;
        std::shared_ptr<Button> _quitButton;

        sf::Text _hzText;
        std::shared_ptr<Input> _hzInput;
        Core *_core;

};

#endif /* !MENU_HPP_ */
