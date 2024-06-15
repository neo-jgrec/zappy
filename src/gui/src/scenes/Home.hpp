/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** home
*/

#ifndef HOME_HPP_
    #define HOME_HPP_

    #include "IScene.hpp"
    #include "../core/Zappy.hpp"
    #include "../ui/Button.hpp"
    #include "../ui/Input.hpp"

    #include <memory>

class Home : public IScene {
    public:
        Home(Zappy &zappy);
        ~Home() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;

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
