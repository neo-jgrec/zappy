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
    #include "../core/Zappy.hpp"

class Menu : public IScene {
    public:
        Menu(Zappy &zappy);
        ~Menu() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;

    protected:
    private:
        std::vector<std::shared_ptr<Button>> _resolutionButtons;
        std::shared_ptr<Button> _fullscreenButton;
        Zappy &_zappy;
};

#endif /* !MENU_HPP_ */
