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

    #include <memory>
    #include <map>

class Core;

class Starlings  {
    public:
        Starlings() {
            _rotation = Random::random(0, 360);
            respawn();
        }

        void respawn() {
            int edge = Random::random(0, 4);
            if (edge == 0)
                _pos = sf::Vector2f(Random::random(0, 1920), 0);
            else if (edge == 1)
                _pos = sf::Vector2f(Random::random(0, 1920), 1080);
            else if (edge == 2)
                _pos = sf::Vector2f(0, Random::random(0, 1080));
            else
                _pos = sf::Vector2f(1920, Random::random(0, 1080));
            edge = Random::random(0, 4);
            if (edge == 0)
                _target = sf::Vector2f(Random::random(0, 1920), 0);
            else if (edge == 1)
                _target = sf::Vector2f(Random::random(0, 1920), 1080);
            else if (edge == 2)
                _target = sf::Vector2f(0, Random::random(0, 1080));
            else
                _target = sf::Vector2f(1920, Random::random(0, 1080));
        }

        void update(float fElapsedTime) {
            _pos = Lerp::moveTo(_pos, _target, 100 * fElapsedTime, 5.f);
            if (_pos.x == _target.x && _pos.y == _target.y)
                respawn();
            _rotation += fElapsedTime * 10;
        }

        float _rotation = 0;
        sf::Vector2f _pos;
        sf::Vector2f _target;
    protected:
    private:
};

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

        sf::Text _title;
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
