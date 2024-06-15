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

    #include "../../core/Zappy.hpp"
    #include "../../sprites/Sprite.hpp"

class World : public IScene {
    public:
        World(Zappy &zappy, sf::Vector2f gameSize) : _gameSize(gameSize), _zappy(zappy) {
            _worldSize = sf::Vector2f(_gameSize.x + 10, _gameSize.y + 10);
            init();
        }
        ~World() {}

        void init();
        bool moveMap(sf::Event event);

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;

        sf::Vector2f _offset;
    private:
        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;
        sf::Vector2f _tileSize;

        sf::Vector2f _gameSize;
        sf::Vector2f _worldSize;
        // sf::Vector2f _viewSize;
        std::vector<std::vector<Chunck>> _chuncks;

        sf::View _view;
        float _zoom = 1;
        float _zoomSpeed = 0.1;
        float _moveSpeed = 10;

        bool _isDragging = false;
        sf::Vector2f _dragStart = sf::Vector2f(0, 0);
        sf::Vector2f _tmpOffset = sf::Vector2f(0, 0);

        Zappy &_zappy;
        sf::Vector2f _hoveredTile;
        Diamond _diamond;
        sf::Vector2f _mousePos;
};


#endif /* !WORLD_HPP_ */
