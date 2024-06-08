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
#include "../sprites/sprite.hpp"
#include "../utils/PerlinNoise.hpp"

class World {
    public:
        World(sf::Vector2i size) : _size(size) {
            PerlinNoise noise;

    
            for (int i = 0; i < size.x; i++) {
                std::vector<Chunck> chuncks;
                for (int j = 0; j < size.y; j++) {
                    Chunck chunck;
                    chunck._pos = sf::Vector2i(i, j);
                    chunck._yOffset = noise.noise(i * 0.1, j * 0.1);
                    chuncks.push_back(chunck);
                }
                _chuncks.push_back(chuncks);
            }
        }
        ~World() {}

        void init(std::map<std::string, std::shared_ptr<Sprite>> sprites) {
            _sprite = sprites["grass"];
            _tileSize = sf::Vector2f(
                _sprite->_sprite.getTexture()->getSize().x,
                _sprite->_sprite.getTexture()->getSize().y
            );
            _worldSize = sf::Vector2f((_size.x * _tileSize.x) / 2 + (_size.y * _tileSize.x) / 2,
                (_size.x * _tileSize.y) / 2 + (_size.y * _tileSize.y) / 2);

        }

        void draw(sf::RenderWindow &window);
        void move(sf::Vector2f dir) {
            _pos += dir;
        }
        void reset() {
            _pos = sf::Vector2f(0, 0);
        }

        sf::Vector2f _offset;
    private:
        std::shared_ptr<Sprite> _sprite;
        sf::Vector2f _tileSize;
        sf::Vector2f _worldSize;

        sf::Vector2f _pos;
        sf::Vector2f _size;
        std::vector<std::vector<Chunck>> _chuncks;
};

#endif /* !WORLD_HPP_ */
