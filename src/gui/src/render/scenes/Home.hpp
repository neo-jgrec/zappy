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

    #include <memory>

class Core;
class Home : public IScene {
    public:
        Home(Core *core, int port, std::string ip);
        ~Home() {}

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;
        void init() override {}
        bool connectToServer();


    protected:
    private:

        sf::Text _title;
        std::shared_ptr<Button> _quitButton;
        std::shared_ptr<Button> _startButton;

        std::shared_ptr<Input> _ipButton;
        std::shared_ptr<Input> _portButton;

        Core *_core;

        std::shared_ptr<Chat> _chat;
};

#endif /* !HOME_HPP_ */
