/*
** EPITECH PROJECT, 2024
** zappy
** File description:
** sprite
*/

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

    #include <SFML/Graphics.hpp>
    #include <iostream>


class Sprite {
    public:
        Sprite(const std::string &path, int frameCount = 1, float frameTime = 0.1f) : _frame(0), _frameCount(frameCount), _frameTime(frameTime)
        {
            _path = path;
            if (!_texture.loadFromFile(path))
                throw std::runtime_error("Cannot load texture");
            _sprite.setTexture(_texture);
            _frameSize = sf::Vector2u(_texture.getSize().x / _frameCount, _texture.getSize().y);
            _sprite.setOrigin(_frameSize.x / 2, _frameSize.y / 2);
            _sprite.setTextureRect(sf::IntRect(0, 0, _frameSize.x, _frameSize.y));
        }
        ~Sprite() {};

        void setPosition(sf::Vector2f pos) { _sprite.setPosition(pos); }
        sf::Vector2f getPosition() { return _sprite.getPosition(); }
        void setSize(sf::Vector2f size) {
            _sprite.setScale(size);
        }
        void draw(sf::RenderWindow &window) { window.draw(_sprite); }
        int update(float fElapsedTime);
        void disableLooping() { _looping = false; }
        void setFrame(int frame) {
            if (frame < _frameCount)
                _frame = 0;
            _sprite.setTextureRect(sf::IntRect(_frame * _frameSize.x, 0, _frameSize.x, _frameSize.y));
            _sprite.setOrigin(_frameSize.x / 2, _frameSize.y / 2);
        }
        bool mouseOver(sf::RenderWindow &window) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);
            sf::FloatRect bounds = _sprite.getGlobalBounds();
            return bounds.contains(worldPos);
        }

        sf::Sprite _sprite;
    private:
        sf::Texture _texture;
        sf::Vector2u _frameSize;
        bool _looping = true;

        int _frame;
        int _frameCount;
        float _frameTime;
        float _time;
        std::string _path;
};

#endif /* !SPRITE_HPP_ */
