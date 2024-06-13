/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** world
*/

#ifndef WORLD_HPP_
#define WORLD_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

#include "chunck.hpp"
#include "../../utils/PerlinNoise.hpp"
#include "../IScene.hpp"
#include "shape/diamond.hpp"

#include "../../core/zappy.hpp"

class World : public IScene {
    public:
        World(Zappy &zappy, sf::Vector2f gameSize) : _gameSize(gameSize), _zappy(zappy) {
            _worldSize = sf::Vector2f(_gameSize.x + 10, _gameSize.y + 10);
            init();
        }
        ~World() {}

        void init() {
            PerlinNoise noise;

            for (int i = 0; i < _worldSize.x; i++) {
                std::vector<Chunck> chuncks;
                for (int j = 0; j < _worldSize.y; j++) {
                    Chunck chunck;
                    chunck._pos = sf::Vector2i(i, j);
                    chunck._yOffset = noise.noise(i * 0.1, j * 0.1);
                    chuncks.push_back(chunck);
                }
                _chuncks.push_back(chuncks);
            }
            _sprite = std::make_shared<Sprite>("./assets/grass.png");
            _tileSize = sf::Vector2f(
                _sprite->_sprite.getTexture()->getSize().x,
                _sprite->_sprite.getTexture()->getSize().y
            );
            _diamond = Diamond(_tileSize);
            // sf::Vector2f _viewSize = sf::Vector2f((_worldSize.x * _tileSize.x) / 2 + (_worldSize.y * _tileSize.x) / 2,
            //     (_worldSize.x * _tileSize.y) / 2 + (_worldSize.y * _tileSize.y) / 2);
            _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
            _view.setSize(sf::Vector2f(1920 , 1080));

        }

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
};


#endif /* !WORLD_HPP_ */
