/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** home
*/

#ifndef HOME_HPP_
    #define HOME_HPP_

    #include "IScene.hpp"
    #include "../ui/Button.hpp"
    #include "../ui/Input.hpp"
    #include "../ui/Chat.hpp"
    #include "../sprites/Sprite.hpp"
    #include "../../utils/Lerp.hpp"
    #include "../../utils/Random.hpp"
    #include "Starlings.hpp"

    #include <memory>
    #include <map>

class Core;

class Home : public IScene {
    public:
        Home(Core *core, int port, std::string ip);
        ~Home() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;
        void init() override {}
        bool connectToServer();

    protected:
    private:

        std::shared_ptr<Button> _quitButton;
        std::shared_ptr<Button> _startButton;

        std::shared_ptr<Input> _ipButton;
        std::shared_ptr<Input> _portButton;

        Core *_core;

        std::shared_ptr<Chat> _chat;

        std::map<std::string, std::shared_ptr<Sprite>> _sprites;

        void initSprites();
        std::vector<Starlings> _starlings;
};

#endif /* !HOME_HPP_ */
