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
        enum panelState {
            TROPHY,
            FLAG,
            TRANTORIAN,
            NONE
        };
        WorldUi(World *world)
        {
            _world = world;
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/trophyButton.png", sf::Vector2f(0, 16*4 * 0), sf::Vector2f(16, 16), 4));
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/flagButton.png", sf::Vector2f(0, 16*4 * 1), sf::Vector2f(16, 16), 4));
            _layer1.push_back(std::make_shared<AdvancedButton>("./assets/flags/trantorianButton.png", sf::Vector2f(0, 16*4 * 2), sf::Vector2f(16, 16), 4));
            _layer2["closeButton"] = std::make_shared<AdvancedButton>("./assets/flags/closeButton.png", sf::Vector2f(16 * 4 *7, 0), sf::Vector2f(16, 16), 4);
            _layer2["prevButton"] = std::make_shared<AdvancedButton>("./assets/flags/prevButton.png", sf::Vector2f(16 * 4 + 8, 64), sf::Vector2f(16, 16), 4);
            _layer2["nextButton"] = std::make_shared<AdvancedButton>("./assets/flags/nextButton.png", sf::Vector2f(16 * 4 * 6 - 8, 64), sf::Vector2f(16, 16), 4);
            _sprites["inventory"] = std::make_shared<Sprite>("./assets/inventory.png");
            _sprites["food"] = std::make_shared<Sprite>("./assets/ressources/food.png");
            _sprites["trantorian"] = std::make_shared<Sprite>("./assets/trantorian.png");
            _sprites["trophyPanel"] = std::make_shared<Sprite>("./assets/flags/trophyPanel.png");
            _sprites["trophyPanel"]->setPosition(sf::Vector2f(16 * 4, 0));
            _sprites["trophyPanel"]->resetOrigin();
            _sprites["trophyPanel"]->setScale(4);
            _sprites["trantorianPanel"] = std::make_shared<Sprite>("./assets/flags/trantorianPanel.png");
            _sprites["trantorianPanel"]->setPosition(sf::Vector2f(16 * 4, 0));
            _sprites["trantorianPanel"]->resetOrigin();
            _sprites["trantorianPanel"]->setScale(4);
            _sprites["flagPanel"] = std::make_shared<Sprite>("./assets/flags/flagPanel.png");
            _sprites["flagPanel"]->setPosition(sf::Vector2f(16 * 4, 0));
            _sprites["flagPanel"]->resetOrigin();
            _sprites["flagPanel"]->setScale(4);
            _sprites["bousolle"] = std::make_shared<Sprite>("./assets/bousolle.png");
            _sprites["bousolle"]->setScale(0.5);
            _font.loadFromFile("assets/BadComic-Regular.ttf");
            _inventoryText = sf::Text("", _font, 25);
        }
        ~WorldUi() {}

        void init() override;
        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;

        void drawInventoryTile(int nb, sf::RenderWindow &window, std::string name);
        void drawRanking(sf::RenderWindow &window);
        void drawTeam(sf::RenderWindow &window);
        void drawTrantorian(sf::RenderWindow &window);

        void drawTileInventory(sf::RenderWindow &window);
        void drawPlayerInventory(sf::RenderWindow &window);

        panelState getPanelState() { return _panelState; }
        int _idPlayer = 0;
        int _idTeam = 0;

    protected:
    private:
        World *_world;
        std::vector<std::shared_ptr<AdvancedButton>> _layer1;
        std::map<std::string, std::shared_ptr<AdvancedButton>> _layer2;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;
        sf::Text _inventoryText;
        panelState _panelState = NONE;
        sf::Font _font;

};

#endif /* !WORLDUI_HPP_ */
