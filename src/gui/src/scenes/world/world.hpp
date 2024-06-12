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

#include "../../core/zappy.hpp"

class World : public IScene {
    public:
        World(Zappy &zappy, sf::Vector2f gameSize) : _gameSize(gameSize), _zappy(zappy) {
            _pressTime = 0;
            _worldSize = sf::Vector2f(_gameSize.x + 10, _gameSize.y + 10);
            init();
            initTileShape();
        }
        ~World() {}

        void initTileShape() {
            _tileShape.setPointCount(4);
            _tileShape.setPoint(0, sf::Vector2f(_tileSize.x / 2, 0));
            _tileShape.setPoint(1, sf::Vector2f(_tileSize.x, _tileSize.y / 4));
            _tileShape.setPoint(2, sf::Vector2f(_tileSize.x / 2, _tileSize.y / 2));
            _tileShape.setPoint(3, sf::Vector2f(0, _tileSize.y / 4));
            _tileShape.setFillColor(sf::Color::Green);
        }

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
            // _viewSize = sf::Vector2f((_worldSize.x * _tileSize.x) / 2 + (_worldSize.y * _tileSize.x) / 2,
            //     (_worldSize.x * _tileSize.y) / 2 + (_worldSize.y * _tileSize.y) / 2);
            _sprites["halo1"] = std::make_shared<Sprite>("./assets/halo1.png");
        }

        bool moveMap(sf::Event event);

        bool update(sf::Event event, sf::RenderWindow &window) override;
        void draw(sf::RenderWindow &window) override;

        sf::Vector2f _offset;
    private:
        std::shared_ptr<Sprite> _sprite;
        std::map<std::string, std::shared_ptr<Sprite>> _sprites;
        sf::Vector2f _tileSize;

        sf::Vector2f _pos;
        sf::Vector2f _gameSize;
        sf::Vector2f _worldSize;
        // sf::Vector2f _viewSize;
        std::vector<std::vector<Chunck>> _chuncks;

        sf::View _view;

        float _pressTime;
        bool _isPressed;
        sf::Vector2f _lastPos;

        Zappy &_zappy;
        sf::ConvexShape _tileShape;
        sf::Vector2f _hoveredTile;
};

#endif /* !WORLD_HPP_ */
