/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WinScene
*/

#ifndef WINSCENE_HPP_
#define WINSCENE_HPP_

    #include <memory>

    #include "IScene.hpp"
    #include "../ui/Button.hpp"
    #include "../ui/Input.hpp"
    #include "../sprites/Sprite.hpp"

class Core;

class WinScene : public IScene {
    public:
        WinScene(Core *core);
        ~WinScene() {

        }

        bool update(sf::Event event, sf::RenderWindow &window) override
        {
            if (_quitButton->update(event, window))
                window.close();
            _homeButton->update(event, window);
            return false;
        }

        void update(float /*fElapsedTime*/) override
        {

        }

        void draw(sf::RenderWindow &window) override;

        void init() override
        {

        }

        void getBackHome();
    protected:
    private:
        Core *_core;
        std::shared_ptr<Button> _homeButton;
        std::shared_ptr<Button> _quitButton;
        sf::Text _text;
        std::shared_ptr<Sprite> _win;

};

#endif /* !WINSCENE_HPP_ */
