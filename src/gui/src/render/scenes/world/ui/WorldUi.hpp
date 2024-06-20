/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** WorldUi
*/

#ifndef WORLDUI_HPP_
#define WORLDUI_HPP_

#include "../../IScene.hpp"
#include "../../../ui/AdvancedButton.hpp"
#include <vector>
#include <memory>


class World;

class WorldUi : public IScene {
    public:
        WorldUi(World *world)
        {
            _world = world;
            _layer1.push_back(std::make_shared<AdvancedButton>(sf::Vector2f(0, 0), sf::Vector2f(100, 100), std::make_shared<Sprite>("./assets/flags/empty_flags.png")));
        }
        ~WorldUi() {}

        void init() override;
        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;

    protected:
    private:
        World *_world;
        std::vector<std::shared_ptr<AdvancedButton>> _layer1;
};

#endif /* !WORLDUI_HPP_ */
