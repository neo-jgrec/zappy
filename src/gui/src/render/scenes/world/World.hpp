/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <memory>
    #include <functional>
    #include <vector>
    #include <iostream>

    #include "../../../utils/PerlinNoise.hpp"
    #include "Chunck.hpp"
    #include "Trantorian.hpp"
    #include "../IScene.hpp"
    #include "shape/diamond.hpp"

    #include "../../sprites/Sprite.hpp"
    #include "../../core/Setting.hpp"
    #include "../../ui/Chat.hpp"
    #include "ui/WorldUi.hpp"
    #include "ui/Ranking.hpp"
    #include "ui/Bubble.hpp"
    #include "ui/LvlUpAnim.hpp"
    #include "../Starlings.hpp"

static const std::vector<std::string> _elements = {
    "tree2", "tree4", "stone1", "grass", "grass2"
};

static const std::vector<sf::Color> _teamsColor = {
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color(255, 165, 0),
    sf::Color::Magenta,
};

class Core;
class World : public IScene {
    public:
        World(Core *core);
        ~World() {}

        void init() override;
        bool update(sf::Event event, sf::RenderWindow &window) override;
        void update(float fElapsedTime) override;
        void draw(sf::RenderWindow &window) override;

        int getNbTrantorian() { return _trantorians.size(); }
        Trantorian getTrantorian(int id) { return _trantorians[id]; }

        void iterateWorld(std::function<void(int, int)> func){
            for (int i = 0; i < _worldSize.x; i++) {
                for (int j = 0; j < _worldSize.y; j++) {
                    func(i, j);
                }
            }
        }
        std::vector<std::string> _teams;
        sf::Vector2f _selectedTile = sf::Vector2f(-1, -1);
        std::vector<std::vector<Chunck>> _chuncks;
        std::vector<Ranking> _rankings;
        void lookTrantorian(int index);
    private:
        void reset();
        void getServerInit();
        void initMap();

        void layer1(int i, int j);
        void layer2(int i, int j);

        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;

        sf::Vector2f _worldSize;
        std::vector<Trantorian> _trantorians;

        sf::View _view;
        sf::Vector2f _pos = sf::Vector2f(0, 0);
        sf::Vector2f _offset;
        sf::Vector2f _tmpOffset = sf::Vector2f(0, 0);
        sf::Text _bubbleText;
        std::vector<Bubble> _bubbles;

        bool _isDragging = false;
        sf::Vector2f _dragStart = sf::Vector2f(0, 0);
        float _zoom = 1;
        float _zoomSpeed = 0.1;
        float _moveSpeed = 10;

        Core *_core;
        sf::Vector2f _hoveredTile;
        sf::Vector2f _mousePos;
        std::shared_ptr<Chat> _chat;

        Diamond _diamond;
        WorldUi _worldUi;
        float _rankTime = 0;
        int _nbIncantations = 0;
        std::vector<LvlUpAnim> _lvlUpAnims;
        std::vector<Starlings> _starlings;

        std::vector<std::vector<int>> _buildings;
        std::map<std::string, sf::Music> _sounds;
        sf::FloatRect _viewRect;
        bool moveMap(sf::Event event);
        void updateTrantorians();
        void updateChuncks();
        void updateIncantation();
        void initSounds();
        bool drawBuilding(sf::RenderWindow &window, int i, int j);
        bool drawTrantorian(sf::RenderWindow &window, int i, int j);
};


#endif /* !WORLD_HPP_ */
