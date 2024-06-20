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
#include "../../../sprites/Sprite.hpp"

class World;

class WorldUi : public IScene {
    public:
        WorldUi(World *world)
        {
            _world = world;
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/trophyButton.png", sf::Vector2f(0, 16*4 * 0), sf::Vector2f(16, 16), 4));
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/flagButton.png", sf::Vector2f(0, 16*4 * 1), sf::Vector2f(16, 16), 4));
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/tileButton.png", sf::Vector2f(0, 16*4 * 2), sf::Vector2f(16, 16), 4));
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/trantorianButton.png", sf::Vector2f(0, 16*4 * 3), sf::Vector2f(16, 16), 4));
            _panel = std::make_shared<Sprite>("./assets/flags/panel.png");
            _panel->setPosition(sf::Vector2f(16 * 4, 0));
            _panel->resetOrigin();
            _panel->setScale(4);
            _sprites["inventory"] = std::make_shared<Sprite>("./assets/inventory.png");
            _sprites["food"] = std::make_shared<Sprite>("./assets/ressources/food.png");
            _sprites["trantorian"] = std::make_shared<Sprite>("./assets/trantorian.png");
            _font.loadFromFile("assets/BadComic-Regular.ttf");
            _inventoryText = sf::Text("", _font, 25);
            // _sprites["ressources"] = std::make_shared<Sprite>("./assets/ressources/ressources.png");
        }
        ~WorldUi() {}

        void init() override;
        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;

        void drawInventoryTile(int nb, sf::RenderWindow &window, std::string name);

        int _teamDisplayed = -1;
        int _trantorianDisplayed = 0;
        int _eggDisplayed = -1;
        int _displayTeam = 1;

    protected:
    private:
        enum panelState {
            TROPHY,
            FLAG,
            TILE,
            TRANTORIAN,
            NONE
        };
        World *_world;
        std::vector<std::shared_ptr<AdvancedButton>> _layer1;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;
        sf::Text _inventoryText;
        std::shared_ptr<Sprite> _panel;
        panelState _panelState = NONE;
        sf::Font _font;
};

#endif /* !WORLDUI_HPP_ */
