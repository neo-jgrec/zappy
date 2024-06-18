/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#ifndef WORLD_HPP_
    #define WORLD_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>

    #include "../../../utils/PerlinNoise.hpp"
    #include "Chunck.hpp"
    #include "Trantorian.hpp"
    #include "../IScene.hpp"
    #include "shape/diamond.hpp"

    #include "../../sprites/Sprite.hpp"
    #include "../../core/Setting.hpp"

class Core;
class World : public IScene {
    public:
        World(Core *core) : _core(core) {
            _sprite = std::make_shared<Sprite>("./assets/grass.png");
            _diamond = Diamond(sf::Vector2f(TILE_SIZE_X, TILE_SIZE_Y));
            _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
            _sprites["hover1"] = std::make_shared<Sprite>("./assets/hover1.png");
            _sprites["trantorian"] = std::make_shared<Sprite>("./assets/trantorian.png");
            _view.setSize(sf::Vector2f(1920 , 1080));

            // for (int i = 0; i < 10; i++) {
            //     Trantorian trantorian(*_sprites["trantorian"]);
            //     trantorian._tile = sf::Vector2f(rand() % (int)_worldSize.x, rand() % (int)_worldSize.y);
            //     _trantorians.push_back(trantorian);
            // }
        }
        ~World() {}

        void init() override;
        bool moveMap(sf::Event event);

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;
        void drawChunck(sf::RenderWindow &window, int i, int j);

        void updateTrantorians();

    private:
        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;

        sf::Vector2f _worldSize;
        std::vector<Trantorian> _trantorians;
        std::vector<std::vector<Chunck>> _chuncks;

        sf::View _view;
        sf::Vector2f _pos = sf::Vector2f(0, 0);
        sf::Vector2f _offset;
        sf::Vector2f _tmpOffset = sf::Vector2f(0, 0);

        bool _isDragging = false;
        sf::Vector2f _dragStart = sf::Vector2f(0, 0);
        float _zoom = 1;
        float _zoomSpeed = 0.1;
        float _moveSpeed = 10;

        Core *_core;
        sf::Vector2f _hoveredTile;
        sf::Vector2f _selectedTile = sf::Vector2f(-1, -1);
        sf::Vector2f _mousePos;

        // ----- this is temporary -----
        Diamond _mapDiamond;
        Diamond _diamond;
};


#endif /* !WORLD_HPP_ */
