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

    #include "Chunck.hpp"
    #include "../IScene.hpp"
    #include "shape/diamond.hpp"

    #include "../../sprites/Sprite.hpp"

static const int TILE_SIZE_X = 95;
static const int TILE_SIZE_Y = 97;
static const int TILE_SIZE_MX = 46;
static const int TILE_SIZE_MY = 27;

class Core;
class World : public IScene {
    public:
        World(Core *core, sf::Vector2f worldSize) : _worldSize(worldSize), _core(core) {
            init();
        }
        ~World() {}

        void init();
        bool moveMap(sf::Event event);

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;

    private:
        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;

        sf::Vector2f _worldSize;
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
        Diamond _diamond;
        sf::Vector2f _mousePos;
        Diamond _mapDiamond;
};


#endif /* !WORLD_HPP_ */
